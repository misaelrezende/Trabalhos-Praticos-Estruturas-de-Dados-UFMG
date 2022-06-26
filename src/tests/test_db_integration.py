from db.create_db import *
from model.model import Model
import pytest

users = [(1, 123456, '123456')]

president_candidates = \
    [(13, 'Luiz Inácio Lula da Silva', 'PT'),
    (22, 'Jair Messias Bolsonaro', 'PL'),
    (12, 'Ciro Gomes', 'PDT'),
    (15, 'Simone Nassar Tebet', 'MDB')
    ]

senator_candidates = \
    [(451, 'Aécio Neves', 'PSDB'),
    (202, 'Cleitinho', 'PSC'),
    (553, 'Alexandre Silveira', 'PSD'),
    (124, 'Duda Salabert', 'PDT')
    ]

president_voting_results = \
    [(1, 13, 'Luiz Inácio Lula da Silva', 0), 
    (2, 22, 'Jair Messias Bolsonaro', 0),
    (3, 12, 'Ciro Gomes', 0),
    (4, 15, 'Simone Nassar Tebet', 0),
    (5, 0, 'Nulo', 0)
    ]

senator_voting_results = \
    [(1, 451, 'Aécio Neves', 0),
    (2, 202, 'Cleitinho', 0),
    (3, 553, 'Alexandre Silveira', 0),
    (4, 124, 'Duda Salabert', 0),
    (5, 0, 'Nulo', 0)
    ]

class TestDBIntegration:
    database_path = "src/tests/test.db"
    @pytest.fixture(scope="session")
    def setup(self):
        """
        Create a new database to test the
        integration with sqlite3 db
        """
        db_in_memory = CreateDB(self.database_path)
        db_in_memory.create_table(sql_create_voter_table)
        db_in_memory.create_table(sql_create_president_candidate_table)
        db_in_memory.create_table(sql_create_senator_candidate_table)
        db_in_memory.create_table(sql_create_president_voting_resulting_table)
        db_in_memory.create_table(sql_create_senator_voting_resulting_table)
        db_in_memory.create_table(sql_create_user_table)

        for user in users:
            db_in_memory.create_user(user)

        voters = [
                (1234567891011, "Conceição Evaristo", 1, 123),
                (4567891011123, "Graciliano Ramos", 1, 456),
                (7891011121314, "Joaquim Maria Machado de Assis", 4, 123)
                ]

        for voter in voters:
            db_in_memory.create_voter(voter)

        for candidate in president_candidates:
            db_in_memory.create_candidate(candidate, 'Presidente')

        for candidate in senator_candidates:
            db_in_memory.create_candidate(candidate, 'Senador')

        for candidate in president_voting_results:
            db_in_memory.create_voting_results_table(candidate, 'Presidente')

        for senator in senator_voting_results:
            db_in_memory.create_voting_results_table(senator, 'Senador')

    # Test voter is enabled to vote
    def test_voter_can_vote(self, setup):
        model = Model(self.database_path)
        voter_registration_number = 4567891011123
        voter_verification = model.verify_voter(voter_registration_number)
        assert voter_verification == 1

    # Test voter in not enabled to vote
    def test_voter_cannot_vote(self, setup):
        model = Model(self.database_path)
        voter_registration_number = 7891011121314
        voter_verification = model.verify_voter(voter_registration_number)
        assert voter_verification == 4

    # Test vote is computed
    def test_compute_vote(self, setup):
        model = Model(self.database_path)
        senator_votes_before = model.get_candidate_votes('Senador', 124)
        model.compute_vote('Senador', 124)
        senator_votes_after = model.get_candidate_votes('Senador', 124)

        assert(senator_votes_before + 1 == senator_votes_after)

    # Test voter has voted
    def test_compute_voter_has_voted(self, setup):
        model = Model(self.database_path)
        voter_registration_number = 4567891011123
        model.compute_voter_has_voted(voter_registration_number)
        voter_verification = model.verify_voter(voter_registration_number)
        assert voter_verification == 4

    # Test vote is null
    def test_president_null_vote(self):
        model = Model(self.database_path)
        null_votes_before = model.get_candidate_votes('Presidente', 0)

        model.compute_vote('Presidente', 43)

        null_votes_after = model.get_candidate_votes('Presidente', 0)

        assert(null_votes_before + 1 == null_votes_after)

    # Test get candidate
    def test_get_candidate_that_exists(self):
        model = Model(self.database_path)
        candidate_info = model.get_candidate_info('Senador', 124)
        assert candidate_info['name'] == 'Duda Salabert'
        assert candidate_info['political_party'] == 'PDT'

    # Test get candidate that does not exist
    def test_get_non_existent_candidate(self):
        model = Model(self.database_path)
        candidate_info = model.get_candidate_info('Senador', 420)
        assert candidate_info['name'] == ''
        assert candidate_info['political_party'] == ''

    def test_user_can_login(self):
        model = Model(self.database_path)
        result = model.login('123456', '123456')
        assert result == True

    def test_count_valid_votes(self):
        model = Model(self.database_path)
        model.compute_vote('Presidente', 13)
        model.compute_vote('Presidente', 15)
        model.compute_vote('Presidente', 43)
        model.compute_vote('Presidente', 13)

        _, total_votes = model.get_election_results('Presidente')
        assert total_votes == 3

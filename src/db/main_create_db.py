"""Main CreateDB module"""
from create_db import *

users = [(1, 123456, '123456')]

voters = \
    [(1234567891011, "Conceição Evaristo", 1, 123),
    (4567891011123, "Graciliano Ramos", 4, 456),
    (7891011121314, "Joaquim Maria Machado de Assis", 4, 123)
    ]

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

def create_db():
    """
    create_db method. This method contains the script
    responsible to create the database
    """
    db = CreateDB("voting_system.db")

    db.create_table(sql_create_voter_table)
    db.create_table(sql_create_president_candidate_table)
    db.create_table(sql_create_senator_candidate_table)
    db.create_table(sql_create_president_voting_resulting_table)
    db.create_table(sql_create_senator_voting_resulting_table)
    db.create_table(sql_create_user_table)

    for user in users:
        db.create_user(user)


    for voter in voters:
        db.create_voter(voter)


    for candidate in president_candidates:
        db.create_candidate(candidate, 'Presidente')

    for candidate in senator_candidates:
        db.create_candidate(candidate, 'Senador')

    for candidate in president_voting_results:
        db.create_voting_results_table(candidate, 'Presidente')

    for senator in senator_voting_results:
        db.create_voting_results_table(senator, 'Senador')

if __name__ == "__main__":
    create_db()

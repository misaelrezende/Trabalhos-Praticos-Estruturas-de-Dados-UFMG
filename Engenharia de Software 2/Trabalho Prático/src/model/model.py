"""Model module"""
from db.access_db import AccessDB

valid_candidates = {
    'Presidente': [12, 13, 15, 22],
    'Senador': [124, 202, 553, 451]
}

class Model:
    """
    Model class. This class is responsible to interact
    with AccessDB, which is the class responsible to access the database
    """
    def __init__(self, db_path = "../db/voting_system.db"):
        self.database_path = db_path

    def get_election_results(self, candidate_type):
        """
        Get vote count from candidate_voting_result table
        Arguments:
            candidate_type (str): position that candidate is running for
        Returns:
            election_results (list): list of tuple of candidate and number of votes received
            total_votes (int): overall number of valid votes
        """
        db = AccessDB(self.database_path)
        election_results = db.get_vote_count(candidate_type)
        db.close_connection()

        # Count valid votes
        total_votes = 0
        for name, votes in election_results:
            if name != "Nulo":
                total_votes = total_votes + votes

        return election_results, total_votes

    def login(self, login_number, login_password):
        """
        Check if user is able to login the voting system
        Arguments:
            login_number (int): login
            login_password (int): password
        Returns:
            The return value (bool): True if enabled. False if not enabled
        """
        db = AccessDB(self.database_path)
        password = db.get_user_data(login_number)
        db.close_connection()

        if password[0] == str(login_password):
            return True
        else:
            return False

    def get_candidate_info(self, candidate_type, candidate_chosen):
        '''
        Get name and political party of candidate
        NOTE Assume input is correct, otherwise vote will be null
        Arguments:
            candidate_type (str): position that candidate is running for
            candidate_chosen (int): political number of candidate
        Returns:
            candidate_info (dict): candidate name and political party
        '''
        candidate_info = {}

        db = AccessDB(self.database_path)
        candidate_info_from_db = db.get_candidate(candidate_type, candidate_chosen)
        db.close_connection()

        if candidate_info_from_db is None:
            candidate_info['name'] = ''
            candidate_info['political_party'] = ''
        else:
            candidate_info['name'] = candidate_info_from_db[0]
            candidate_info['political_party'] = candidate_info_from_db[1]

        return candidate_info

    def verify_voter(self, voter_registration_number):
        """
        Verify if voter is able to vote
        Arguments:
            voter_registration_number (int): registration number
        Returns:
            3 if voter condition is None

            Or else

            voter status (int):
                1: eleitor está apto a votar;
                2: não pode votar;
                3: núm incorreto;
                4: já votou
        """
        db = AccessDB(self.database_path)
        voter_condition = db.get_voter_status('voter', voter_registration_number)
        db.close_connection()

        if voter_condition is None:
            return 3

        return voter_condition[0]

    def compute_voter_has_voted(self, registration):
        """
        Save info that voter has voted
        Arguments:
            registration: registration number of voter
        """
        db = AccessDB(self.database_path)
        db.set_voter_status('voter', registration)
        db.close_connection()

    def compute_vote(self, candidate_type, candidate_chosen):
        """
        Save voter choice to candidate result table
        Arguments:
            candidate_type: position that chosen candidate is running for
            candidate_chosen: political number of chosen candidate
        """
        # Null vote if candidate does not exist
        if candidate_chosen not in valid_candidates[candidate_type]:
            candidate_chosen = 0
        db = AccessDB(self.database_path)
        db.set_voter_choice(candidate_type, candidate_chosen)
        db.close_connection()

    def get_candidate_votes(self, candidate_type, candidate_number):
        """
        Get the quantity of votes from a specific candidate
        Arguments:
            candidate_type: position that chosen candidate is running for
            candidate_chosen: political number of chosen candidate
        Returns:
            (int): quantity of votes
        """
        db = AccessDB(self.database_path)
        candidate_votes = db.get_candidate_vote_count(candidate_type, candidate_number)
        db.close_connection()
        return candidate_votes[1]

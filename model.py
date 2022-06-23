from candidate import Candidate
from voter import Voter
from clerk import Clerk
from db.access_db import AccessDB

# results file header
# candidate_name, # of votes received
# null votes,     # of votes received

# candidates file header
# candidate_name, number, name of party

# voter file header
# voter_registration_number, name, is_able_to_vote

class Model:
    database_path = "db/voting_system.db"

    def get_election_results(self, candidate_type):
        """
        Get vote count from candidate_voting_result table
        Arguments:
            candidate_type: position that candidate is running for
        Returns:
            election_results: list of tuple of candidate and number of votes received
            total_votes: overall number of valid votes
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
        Returns:
            The return value: True if enabled. False if not enabled
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
        '''
        candidate_info = {}

        db = AccessDB(self.database_path)
        candidate_info_from_db = db.get_candidate(candidate_type, candidate_chosen)
        db.close_connection()

        if candidate_info_from_db == None:
            candidate_info['name'] = ''
            candidate_info['political_party'] = ''
        else:
            candidate_info['name'] = candidate_info_from_db[0]
            candidate_info['political_party'] = candidate_info_from_db[1]

        return candidate_info

    # Verify if voter is able to vote
    def verify_voter(self, voter_registration_number):
        # 1: eleitor está apto a votar;
        # 2: não pode votar;
        # 3: núm incorreto;
        # 4: já votou
        db = AccessDB(self.database_path)
        voter_condition = db.get_voter_status('voter', voter_registration_number)
        db.close_connection()

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
        db = AccessDB(self.database_path)
        db.set_voter_choice(candidate_type, candidate_chosen)
        db.close_connection()

    def read_results_from_file(self, candidate_chosen, results_filename):
        results_data = []
        is_null_vote = True
        with open(results_filename, 'r') as results:
            line = results.readline()
            while line != '':
                candidate_name,number,number_of_votes=line.split(',')
                if number == str(candidate_chosen):
                    number_of_votes = str (int(number_of_votes) + 1 )
                    is_null_vote = False

                if is_null_vote == True and candidate_name == 'nulo':
                    results_data.append({
                        'candidate_name': candidate_name,
                        'number': number,
                        'number_of_votes': str( int(number_of_votes) + 1 )
                    })
                else:
                    results_data.append({
                        'candidate_name': candidate_name,
                        'number': number,
                        'number_of_votes': int(number_of_votes)
                    })

                line = results.readline()

        return results_data

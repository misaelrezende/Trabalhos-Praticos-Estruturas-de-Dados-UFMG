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

    # Return election_results, valid_votes
    def get_election_results(self, candidate):
        election_results = []
        total_votes = 0

        # open results file
        results_file = "files/results_{}.txt".format(candidate)
        with open(results_file, 'r') as results:
            line = results.readline()
            while line != '':
                candidate_name,_,number_of_votes = line.split(',')
                election_results.append({
                    'candidate_name': candidate_name,
                    'number_of_votes': int(number_of_votes)
                })

                total_votes += int(number_of_votes)

                line = results.readline()

        return election_results, total_votes

    # Return if user is able to login the voting system
    def login(self, login_number, login_password):
        is_user_allowed = False
        with open("files/users_login.txt", 'r') as reader:
            line = reader.readline()
            while line != '':
                user, password = line.split(',')
                if int(login_number) == int(user):
                    if int(password) == int(login_password):
                        is_user_allowed = True

                line = reader.readline()

        return is_user_allowed

    # Return name and political party of candidate
    # NOTE Assume input is correct and candidate exists
    def get_candidate_info(self, candidate_type, candidate_chosen):
        candidate_info = {}
        is_candidate_valid = False

        with open("files/candidates_{}.txt".format(candidate_type)) as reader:
            line = reader.readline()
            while line != '':
                candidate_name,number,party = line.split(',')
                if int(number) == candidate_chosen:
                    candidate_info['name'] = candidate_name
                    candidate_info['political_party'] = party
                    is_candidate_valid = True

                line = reader.readline()

        if is_candidate_valid == False:
            candidate_info['name'] = ''
            candidate_info['political_party'] = ''

        return candidate_info

    # Verify if voter is able to vote
    def verify_voter(self, voter_registration_number):
        # 1: eleitor está apto a votar;
        # 2: não pode votar;
        # 3: núm incorreto;
        # 4: já votou
        db = AccessDB(self.database_path)
        voter_condition = db.get_voter_status('voter', voter_registration_number)

        return voter_condition[0]

    def compute_voter_has_voted(self, voter_registration_number):
        voters_data = []
        voters_file = "files/voters.txt"
        with open(voters_file, 'r') as reader:
            line = reader.readline()
            while line != '':
                reg_number,name,voter_condition = line.split(',')

                if voter_registration_number == int(reg_number):
                    voters_data.append({
                        'reg_number': reg_number,
                        'name': name,
                        'voter_condition': str(4)
                    })
                else:
                    voters_data.append({
                        'reg_number': reg_number,
                        'name': name,
                        'voter_condition': voter_condition
                    })


                line = reader.readline()

        with open(voters_file, 'w') as writer:
            for voters in voters_data:
                writer.writelines(
                    "{},{},{}\n".format(
                    voters['reg_number'],
                    voters['name'],
                    voters['voter_condition']
                ))

    def compute_vote(self, candidate_type, candidate_chosen):
        results_filename = "files/results_{}.txt".format(candidate_type)

        results_data = self.read_results_from_file(
            self, candidate_chosen, results_filename, results_data
            )
        self.write_new_results_to_file(self, results_filename, results_data)

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

    def write_new_results_to_file(self, results_filename, results_data):
        with open(results_filename, 'w') as writer:
            for candidate_votes in results_data:
                writer.writelines(
                    "{},{},{}\n".format(
                    candidate_votes['candidate_name'],
                    candidate_votes['number'],
                    candidate_votes['number_of_votes']
                ))
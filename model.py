from candidate import Candidate
from voter import Voter
from clerk import Clerk

# results file header
# candidate_name, # of votes received
# null votes,     # of votes received

# candidates file header
# candidate_name, number, name of party

# voter file header
# voter_registration_number, name, is_able_to_vote

class Model:

    # Return election_results, valid_votes
    def get_election_results(self, candidate):
        election_results = {}
        total_valid_votes = 0
        # open results file
        results_file = "files/results_{}.txt".format(candidate)
        with open(results_file, 'r') as results:
            line = results.readline()
            while line != '':
                candidate_name, votes = line.split(',')
                election_results[candidate_name] = int(votes)
                if candidate_name != "nulo":
                    total_valid_votes += int(votes)

                line = results.readline()

        return election_results, total_valid_votes

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
    def get_candidate_info(self, candidate, candidate_chosen):
        candidate_info = {}
        with open("files/candidates_{}.txt".format(candidate)) as reader:
            line = reader.readline()
            while line != '':
                candidate_name,number,party = line.split(',')
                if int(number) == candidate_chosen:
                    candidate_info['name'] = candidate_name
                    candidate_info['political_party'] = party

                line = reader.readline()

        return candidate_info

    # Verify if voter is able to vote
    def verify_voter(self, voter_registration_number):
        # 1: eleitor está apto a votar;
        # 2: não pode votar;
        # 3: núm incorreto;
        # 4: já votou
        is_voter_able = 3
        with open("files/voters.txt", 'r') as reader:
            line = reader.readline()
            while line != '':
                reg_number,name,voter_condition = line.split(',')
                if voter_registration_number == int(reg_number):
                    is_voter_able = int(voter_condition)
                    break
                line = reader.readline()

        return is_voter_able

    def compute_voter_has_voted(self, voter_registration_number):
        voters_data = {}
        with open("files/voters.txt", 'r') as reader:
            line = reader.readline()
            while line != '':
                reg_number,name,voter_condition = line.split(',')
                voters_data['name'] = name
                voters_data['reg_number'] = reg_number
                if voter_registration_number == int(reg_number):
                    voters_data['voter_condition'] = str(4)
                else:
                    voters_data['voter_condition'] = voter_condition

        with open("files/voters.txt", 'w') as writer:
            for reg_number,name,voter_condition in voters_data.items():
                writer.writelines(
                    "{},{},{}\n".format(
                    reg_number,
                    name,
                    voter_condition
                ))

    def compute_vote(self, candidate_type, candidate_chosen):
        results_data = {}
        is_null_vote = True

        # Read results saved
        results_file = "files/results_{}.txt".format(candidate_type)
        with open(results_file, 'r') as results:
            line = results.readline()
            while line != '':
                candidate_name,number_of_votes=line.split(',')
                if candidate_name == candidate_chosen:
                    number_of_votes = int(number_of_votes) + 1
                    number_of_votes = str(number_of_votes)
                    is_null_vote = False

                results_data['candidate_name'] = candidate_name
                results_data['number_of_votes'] = number_of_votes

                line = results.readline()

        if is_null_vote == True:
            results_data['nulo'] = str( int(number_of_votes) + 1 )

        # Write new results
        with open(results_file, 'w') as writer:
            for candidate_name, number_of_votes in results_data.items():
                writer.writelines(
                    "{},{}\n".format(
                    candidate_name,
                    number_of_votes
                ))
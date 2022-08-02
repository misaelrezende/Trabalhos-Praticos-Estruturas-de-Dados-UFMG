"""Controller module"""
import sys
from model.model import Model
from view.view import View
sys.path.append("../")

class Controller:
    """
    Controller class
    """
    is_voting_sistem_authenticated = False
    list_of_candidates = ['Presidente', 'Senador']

    def __init__(self):
        self.model = Model()
        self.view = View()

    def start(self):
        """
        Start the system and login clerk
        """
        option = self.view.start()

        if option == 1: # Login como mesário
            result = self.login()
            if result is True:
                self.view.show_login_detail(result)
                self.is_voting_sistem_authenticated = True
            else:
                self.view.end(False) # Finish system
                return
        else:
            self.view.end(False) # Finish system
            return

    def run_voting_system(self):
        """
        Start voting system if user is correctly authenticated
        Runs while voter registration is not 0 (zero)
        """
        if self.is_voting_sistem_authenticated is True:
            # Initialize computing the votes
            self.view.start_voting_machine()
            voter_registration_number = 1 # flag initialization

            # While voter_registration_number is not zero
            # (zero would conclude the voting session)
            while True:
                voter_registration_number = self.view.get_voter_registration_number()

                if voter_registration_number == 0:
                    result = self.finish_voting_machine()
                    if result is True:
                        self.show_election_results()
                        break

                    continue

                else:
                    voter_verification = self.model.verify_voter(voter_registration_number)
                    if voter_verification == 1:
                        # Voter starts to choose his/her candidates
                        self.start_voting()
                        self.model.compute_voter_has_voted(voter_registration_number)
                    else:
                        self.view.voter_error(voter_verification)

    def show_election_results(self):
        """
        Show election results
        """
        number_of_candidates = len(self.list_of_candidates)
        current_candidate = 0

        while True:
            candidate = self.list_of_candidates[current_candidate]
            election_results, valid_votes = self.model.get_election_results(candidate)
            self.view.show_election_results(candidate, election_results, valid_votes)

            if current_candidate == number_of_candidates-1:
                break
            current_candidate += 1

    def finish_voting_machine(self):
        """
        Check if clerk wants to finish voting system
        """
        clerk_wants_to_finish = self.view.finish_voting_machine()
        if clerk_wants_to_finish == 1:
            result = self.login()
            while result is not True:
                self.view.show_login_detail(result)
                result = self.login()

            self.view.show_login_detail(result)
            self.is_voting_sistem_authenticated = False
            self.view.end(True) # Finish system
            return True # User was authenticated and system can finish

        # User was not authenticated, system can not finish
        # OR user wants to continue the voting process
        return False

    def login(self):
        """
        Login clerk
        """
        login_number, login_password = self.view.get_login_detail()
        is_logged = self.model.login(login_number, login_password)
        return is_logged

    def start_voting(self):
        """
        Start voting. Here the voter chooses his/her candidates
        """
        number_of_candidates = len(self.list_of_candidates)
        current_candidate = 0

        while True:
            candidate_type = self.list_of_candidates[current_candidate]
            candidate_chosen = self.view.get_voter_candidate(candidate_type)
            candidate_info = self.model.get_candidate_info(candidate_type, candidate_chosen)
            self.view.show_candidate_chosen(candidate_info)
            option = self.view.get_voter_candidate_option()

            if option == 'verde':
                self.model.compute_vote(candidate_type, candidate_chosen)
                if current_candidate == number_of_candidates-1:
                    break

                current_candidate += 1
            else:
                continue

        self.view.show_voter_has_finished()

if __name__ == "__main__":
    main = Controller()
    main.start()
    main.run_voting_system()

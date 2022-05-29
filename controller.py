# from model import Model
from view import View

class Controller:
    is_voting_sistem_on = False
    list_of_candidates = ['Presidente', 'Senador'] # dep federal, dep estadual, senador, governador, presidente
    def __init__(self):
        # self.model = Model()
        self.view = View()

    def start(self):
        option = self.view.start()

        if option == 1: # Login como mesário 
            result = self.login()
            if result == True:
                self.view.show_login_detail(result)
                self.is_voting_sistem_on = True
            else:
                self.view.end(False) # Finish system
                return
        else:
            self.view.end(False) # Finish system
            return

        # Voting system started
        if self.is_voting_sistem_on == True:
            # Initialize computing the votes
            self.view.start_voting_machine()
            voter_registration_number = 1

            # While voter_registration_number is not zero
            # (zero would conclude the voting session)
            while(voter_registration_number != 0):
                voter_registration_number = self.view.get_voter_registration_number()
                voter_verification = self.model.verify_voter() # 1: eleitor está apto a votar; 2: não pode votar; 3: núm incorreto; 4: já votou
                if voter_verification == 0:
                    result = self.finish_voting_machine()
                    if result == True:
                        break
                    else:
                        continue
                elif voter_verification == 1:
                    self.start_voting()
                else:
                    self.view.voter_error(voter_verification)

    def finish_voting_machine(self):
        is_finishing = self.view.finish_voting_machine()
        if is_finishing == 1:
            result = self.login()
            while result != True:
                self.view.show_login_detail(result)
                result = self.login()

            self.view.show_login_detail(result)
            self.is_voting_sistem_on = False
            self.view.end(True) # Finish system
            return True # User was authenticated and system can finish

        # User was not authenticated, system can not finish
        # OR user wants to continue the voting process
        return False

    def login(self):
        login_number, login_password = self.view.get_login_detail()
        is_logged = self.model.login(login_number, login_password)
        # is_logged = True # FIXME
        return is_logged

    def start_voting(self):
        for candidate in self.list_of_candidates:
            candidate_chosen = self.view.voter_is_voting(candidate)
            # Check if voter has chosen correctly a valid candidate
            voter_candidate_verification = self.model.verify_voter(candidate_chosen)
            while(voter_candidate_verification != 1):
                # TODO Deal with ERROR issue
                voter_candidate_verification = self.model.verify_voter(candidate)

            self.model.compute_vote(candidate_chosen)

        self.view.voter_is_finished()

if __name__ == "__main__":
    main = Controller()
    main.start()
# from model import Model
from view import View

class Controller:
    is_voting_sistem_on = False
    list_of_candidates = ['Presidente', 'Senador']
    def __init__(self):
        # self.model = Model()
        self.view = View()

    def start(self):
        option = self.view.start()

        if option == 1:
            result = self.login()
            if result == True:
                self.view.show_login_detail(result)
            self.is_voting_sistem_on = True
        else:
            self.view.end(result)
            # self.view.end(False) # FIXME

        if self.is_voting_sistem_on == True:
            # Initialize computing the votes
            self.view.start_voting_machine()
            voter_registration_number = 1

            # While voting number is not zero
            # (zero would conclude the voting session)
            while(voter_registration_number != 0):
                voter_registration_number = int(input("Digite o número do título de eleitor: "))
                voter_verification = self.model.verify_voter() # 1: eleitor está apto a votar; 2: não pode votar; 3: núm incorreto; 4: já votou
                if voter_verification == 1:
                    self.start_voting()

            # TODO Finish implementation
            is_finishing = self.view.finish_voting_machine()
            if is_finishing == True:
                self.view.finish_voting_machine()
            # TODO Finish implementation

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
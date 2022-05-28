# from model import Model
from view import View

class Controller:    
    def __init__(self):
        # self.model = Model()
        self.view = View()

    def start(self):
        option = self.view.start()

        if option == 1:
            result = self.login()
            if result == True:
                self.view.showLoginDetail(result)
                
        else:
            self.view.end(result)
            # self.view.end(False) # FIXME
    
    def login(self):
        login_number, login_password = self.view.getLoginDetail()
        is_logged = self.model.login(login_number, login_password)
        # is_logged = True # FIXME
        return is_logged

if __name__ == "__main__":
    main = Controller()
    main.start()
class User:
    def __init__(self, name, reg_number):
        self.name = name
        self.voter_registration_number = reg_number
    
    def set_name(self, name):
        self.name = name
    
    def get_name(self):
        return self.name


class Voter(User):
    def __init__(self, name, reg_number, poll_station):
        User.__init__(self, name, reg_number)
        self.polling_station = poll_station
    
    def voter_registration_number(self):
        pass

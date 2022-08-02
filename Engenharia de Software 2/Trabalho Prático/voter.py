# pylint: skip-file
from users import User
class Voter(User):
    def __init__(self, name, reg_number, poll_station):
        User.__init__(self, name, reg_number)
        self.polling_station = poll_station
    
    def voter_registration_number(self):
        pass
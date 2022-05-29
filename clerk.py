from users import User
class Clerk(User):
    def _init_(self, startDate, endDate, name, reg_number, zona, secao,listOfCandidate):
        self.starDate = startDate
        self.endDate = endDate
        self.listCandidate = listOfCandidate
        super().__init__(name, reg_number, zona, secao)

    def get_starDate(self):
        return self.starDate

    def get_endDate(self):
        return self.endDate

    def get_listCandidate(self):
        return self.listCandidate     
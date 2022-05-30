from users import User
class Candidate(User):
    def __init__(self, name, reg_number, zona, secao, number, electoralOffice):
        self.number = number
        self.electoralOffice = electoralOffice
        super().__init__(name, reg_number, zona, secao)

    def get_number(self):
        return self.number

    def get_name(self):
        return self.get_name

    def get_electoralOffice(self):
        return self.electoralOffice    
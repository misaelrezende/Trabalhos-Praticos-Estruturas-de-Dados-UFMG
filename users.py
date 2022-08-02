# pylint: skip-file
class User:
    def __init__(self, name, reg_number, zona, secao):
        self.name = name
        self.registration_number = reg_number
        self.zona = zona
        self.secao = secao

    def get_reg_number(self):
        return self.registration_number

    def get_zona(self):
        return self.zona

    def get_secao(self):
        return self.secao

    def get_name(self):
        return self.name
class View:
    def start(self):
        print("### Sistema offline ####\n")
        print("Faça login como mesário para iniciar a votação.")
        return self.menu()

    def menu(self):
        print("0 - Sair")
        print("1 - Para fazer login como mesario")

        return int(input("\nDigite a opção: "))

    def getLoginDetail(self):
        print("\nDigite o numero de login")
        login_number = int(input())
        print("\nDigite a senha de login")
        login_password = int(input())
        return login_number, login_password

    def showLoginDetail(self, result):
        if result == True:
            print()
            print("Mesário autenticado com sucesso!")
        else:
            print()
            print("Mesário não autenticado.")
            print("Por favor, reinicie a autenticação.")

    def end(self, result):
        if result == True:
            print()
            print("### Sistema de votação finalizado com sucesso ###")
        else:
            print()
            print("### Sistema de votação finalizado com erro ###")
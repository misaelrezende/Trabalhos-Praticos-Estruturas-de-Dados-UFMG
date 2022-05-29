class View:
    def start(self):
        print("### Sistema offline ####\n")
        print("Faça login como mesário para iniciar a votação.")
        return self.menu()

    def menu(self):
        print("0 - Sair")
        print("1 - Para fazer login como mesario")

        return int(input("\nDigite a opção: "))

    def get_login_detail(self):
        print("\nDigite o numero de login")
        login_number = int(input())
        print("\nDigite a senha de login")
        login_password = int(input())
        return login_number, login_password
    
    def start_voting_machine(self):
        print("### Sistema de votação iniciada ###")
        print("### Para terminar a votação, digite o número 0 para o titulo de eleitor ###")

    def finish_voting_machine(self):
        print("Você quer finalizar a votação?")
        print("0 - Finalizar votação")
        print("1 - Continuar votação")
        print("Digite o login e senha do mesário")

    def voter_is_voting(self, candidate):
        print("{}".format(candidate))
        return int(input())

    def voter_is_finished(self):
        print("FIM")

    def show_login_detail(self, result):
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
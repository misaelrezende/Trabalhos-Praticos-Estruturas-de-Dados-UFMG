"""View module"""

class View:
    """
    View class. This class is responsible to interact
    with the clerk and the voter
    """
    def start(self):
        """
        Show user that system is offline
        Returns:
            Invoke self.menu() method
        """
        print("### Sistema offline ####\n")
        print("Faça login como mesário para iniciar a votação.")
        return self.menu()

    def menu(self):
        """
        Show the user an option to login or to quit the system
        Returns:
            (int): Option chosen by user
        """
        print("0 - Sair")
        print("1 - Para fazer login como mesario")
        return int(input("\nDigite a opção: "))

    def get_login_detail(self):
        """
        Get login and password of user
        Returns:
            login_number (int): login
            login_password (int): password
        """
        print("\nDigite o numero de login")
        login_number = int(input())
        print("\nDigite a senha de login")
        login_password = int(input())
        return login_number, login_password

    def show_login_detail(self, result):
        """
        Show user that he/her is/is not authenticated
        Arguments:
            result (bool): result of login attempt
        """
        if result is True:
            print()
            print("Mesário autenticado com sucesso!")
        else:
            print()
            print("Mesário não autenticado.")
            print("Por favor, reinicie a autenticação.")

    def start_voting_machine(self):
        """
        Show user that the voting process has started
        """
        print()
        print("### Sistema de votação iniciada ###")
        print("### Para terminar a votação, digite o número 0 para o titulo de eleitor ###")
        print()

    def get_voter_registration_number(self):
        """
        Get the voter registration number
        Returns:
            (int): registration entered by user
        """
        return int(input("Digite o número do título de eleitor: "))

    def finish_voting_machine(self):
        """
        Check if clerk wants to finish voting process
        Returns:
            option (int): if user input is 0
            Or else
            Invoke self.menu() method
        """
        print("Você quer finalizar a votação?")
        print("0 - Continuar votação")
        print("1 - Finalizar votação")
        option = int(input("\nDigite a opção: "))
        if option == 0:
            print()
            return 0

        # User wants to finish voting system
        print()
        print("Para finalizar a votação, escolha a opção 1")
        print("Logo após, será necessário digitar o login e senha do mesário")
        print()
        return self.menu()

    def voter_error(self, error):
        """
        Show user that he/she cannot vote
        or entered an invalid registration number
        """
        if error == 2:
            print()
            print("Eleitor não pode votar.")
            print("Eleitor tem cadastro irregular no TRE.")
            print()
        elif error == 3:
            print()
            print("Número de título de eleitor não reconhecido.")
            print("Digite novamente.")
            print()
        elif error == 4:
            print()
            print("Eleitor já votou nessa eleição.")
            print()

    def get_voter_candidate(self, candidate_type):
        """
        Get candidate choice from user
        Returns:
            (int): number of the candidate
        """
        print("{}: ".format(candidate_type))
        return int(input())

    def show_candidate_chosen(self, candidate_chosen):
        """
        Show the name and political party of the chosen candidate
        """
        print()
        print("{}\n{}"
        .format(candidate_chosen['name'], candidate_chosen['political_party']))

    def get_voter_candidate_option(self):
        """
        Get confirmation of user from entered candidate
        Returns:
            (str): Choice entered by user
        """
        print()
        print("Digite VERDE para CONFIRMAR este voto")
        print("Digite LARANJA para REINICIAR este voto")
        print()
        return input().lower()

    def show_voter_has_finished(self):
        """
        Show final message that voting system has finished
        """
        print()
        print("FIM")
        print()

    def end(self, result):
        """
        Show user if system has finished correctly
        Arguments:
            result (bool): result of shutting down the voting process system
        """
        if result is True:
            print()
            print("### Sistema de votação finalizado com sucesso ###")
        else:
            print()
            print("### Sistema de votação finalizado com erro ###")

    def show_election_results(self, running_candidate, election_results, valid_votes):
        """
        Show the result of voting process. Show elected candidates
        and vote count proportion
        Arguments:
            running_candidate (str): position that candidate is running for
            election_results (list): list of candidate name and their vote count
            valid_votes (int): quantity of valid votes, i.e., total votes count minus null votes
        """
        print()
        print("### Resultados para candidato a {} ###".format(running_candidate))
        print()

        for candidate, votes in election_results:

            if valid_votes == 0:
                print("> {}, \t{} votos, \t{:.2%} dos votos"
                .format(candidate, votes, votes)
                )
            else:
                print("> {}, \t{} votos, \t{:.2%} dos votos"
                .format(candidate, votes, votes/valid_votes)
                )

        sort_election_results = sorted(election_results, key=lambda y: y[1], reverse=True)
        print()
        print("-----------------------------------")
        print("Candidato eleito: {}".format(sort_election_results[0][0]))
        print("-----------------------------------")

"""View module"""

class View():
    """
        View class
    """
    def start(self):
        """
        Show user that system has started
        Returns:
            User choice
        """
        print("## Calculadora básica em Python ##")
        print("Digite quantos números precisar, separados por vírgulas\n")
        print("Digite 0 para Sair")
        print("Digite 1 para Continuar\n")
        return int(input("Eu quero: "))

    def get_user_input(self):
        """
        Get user input.
        Returns:
            User choice and input numbers
        """
        print("\nDigite...")
        print("0 - Para Sair")
        print("1 - Para somar números")
        print("2 - Para subtrair numeros\n")
        operand = int(input("Eu quero: "))
        if operand == 0:
            return 0, None

        user_input = input("\nAgora digite os valores a serem calculados: ")
        return (operand, user_input)

    def show_result(self, result):
        """
        Show result of expression to user.
        Arguments:
            result: float
        """
        print("\nO resultado é igual a: {}\n".format(result))

    def end(self):
        """
        Show message to user that system is finished.
        """
        print("\n## Calculadora encerrada ##")

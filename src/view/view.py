class View():
    def start(self):
        print("## Calculadora básica em Python ##")
        print("Digite quantos números precisar, separados por vírgulas\n")
        print("Digite 0 para Sair")
        print("Digite 1 para Continuar\n")
        return int(input("Eu quero: "))

    def get_user_input(self):
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
        print("\nO resultado é igual a: {}\n".format(result))

    def end(self):
        print("\n## Calculadora encerrada ##")
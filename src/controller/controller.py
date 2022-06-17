import sys
sys.path.append("../")

from model.calculator import Calculator
from view.view import View

class Controller():
    def __init__(self):
        self.model = Calculator()
        self.view = View()

    def start(self):
        first_input = self.view.start()

        if first_input != 0:
            operand, user_input = self.view.get_user_input()

            while operand != 0:
                list_of_numbers = self.parse_user_input(user_input)
                result = self.get_equation_result(operand, list_of_numbers)
                self.view.show_result(result)
                operand, user_input = self.view.get_user_input()

        self.view.end()

    def parse_user_input(self, user_input):
        list_of_inputs = user_input.split(',')
        list_of_string_inputs = [i.strip(' ') for i in list_of_inputs]
        list_of_float_inputs = [float(i) for i in list_of_string_inputs]
        return list_of_float_inputs

    def get_equation_result(self, operand, list_of_numbers):
        if operand == 1:
            return self.model.sum(list_of_numbers)
        elif operand == 2:
            return self.model.subtract(list_of_numbers)

if __name__ == "__main__":
    main = Controller()
    main.start()
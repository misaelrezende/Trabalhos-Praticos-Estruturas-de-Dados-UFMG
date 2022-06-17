# pylint: skip-file
from controller.controller import Controller

class TestController:
    # Sum tests
    def test_sum_one_number(self):
        controller = Controller()
        list_of_numbers = controller.parse_user_input("2")
        result = controller.get_equation_result(1, list_of_numbers)
        assert result == 2

    def test_sum_two_numbers(self):
        controller = Controller()
        list_of_numbers = controller.parse_user_input("1,2")
        result = controller.get_equation_result(1, list_of_numbers)
        assert result == 3

    def test_sum_seven_numbers(self):
        controller = Controller()
        list_of_numbers = controller.parse_user_input("7,3,7,8,0,4,2")
        result = controller.get_equation_result(1, list_of_numbers)
        assert result == 31

    def test_sum_with_negative_numbers(self):
        controller = Controller()
        list_of_numbers = controller.parse_user_input("-1,2")
        result = controller.get_equation_result(1, list_of_numbers)
        assert result == 1

    # Subtraction tests
    def test_subtract_one_number(self):
        controller = Controller()
        list_of_numbers = controller.parse_user_input("5")
        result = controller.get_equation_result(2, list_of_numbers)
        assert result == -5

    def test_subtract_two_numbers(self):
        controller = Controller()
        list_of_numbers = controller.parse_user_input("1,6")
        result = controller.get_equation_result(2, list_of_numbers)
        assert result == -7

    def test_subtract_seven_numbers(self):
        controller = Controller()
        list_of_numbers = controller.parse_user_input("7,3,7,8,0,4,2")
        result = controller.get_equation_result(2, list_of_numbers)
        assert result == -31

    def test_subtract_with_negative_numbers(self):
        controller = Controller()
        list_of_numbers = controller.parse_user_input("-1,2")
        result = controller.get_equation_result(2, list_of_numbers)
        assert result == -1
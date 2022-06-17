from controller.controller import Controller

class TestController:
    def test_sum_one_number(self):
        self.controller = Controller()
        list_of_numbers = self.controller.parse_user_input("2")
        result = self.controller.get_equation_result(1, list_of_numbers)
        assert result == 2

    def test_sum_two_numbers(self):
        self.controller = Controller()
        list_of_numbers = self.controller.parse_user_input("1,2")
        result = self.controller.get_equation_result(1, list_of_numbers)
        assert result == 3
    
    def test_sum_seven_numbers(self):
        self.controller = Controller()
        list_of_numbers = self.controller.parse_user_input("7,3,7,8,0,4,2")
        result = self.controller.get_equation_result(1, list_of_numbers)
        assert result == 31
    
    def test_sum_with_negative_numbers(self):
        self.controller = Controller()
        list_of_numbers = self.controller.parse_user_input("-1,2")
        result = self.controller.get_equation_result(1, list_of_numbers)
        assert result == 1
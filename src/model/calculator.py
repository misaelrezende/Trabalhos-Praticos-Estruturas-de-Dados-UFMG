class Calculator():
    def sum(self, list_of_numbers):
        result = 0
        for number in list_of_numbers:
            result = result + number

        return result

    def subtract(self, list_of_numbers):
        result = 0
        for number in list_of_numbers:
            result = result - number

        return result
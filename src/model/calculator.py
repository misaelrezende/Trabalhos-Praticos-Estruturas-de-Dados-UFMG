"""Calculator module"""

class Calculator():
    """
        Calculator class
    """
    def sum(self, list_of_numbers):
        """
        Sums a list of numbers
        Arguments:
            list_of_numbers: list of float
        Returns:
            Result: float
        """
        result = 0
        for number in list_of_numbers:
            result = result + number

        return result

    def subtract(self, list_of_numbers):
        """
        Subtract a list of numbers
        Arguments:
            list_of_numbers: list of float
        Returns:
            Result: float
        """
        result = 0
        for number in list_of_numbers:
            result = result - number

        return result

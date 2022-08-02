"""AccessDB module"""
import sqlite3
from sqlite3 import Error

class AccessDB:
    """
    AccessDB class. This class is responsible to directly interact
    with the database
    """
    def __init__(self, database_file):
        self.connection = None
        self.create_connection(database_file)

    def create_connection(self, database_file):
        """
        Create a database connection to a SQLite database
        Arguments:
            database_file: database file
        """
        try:
            self.connection = sqlite3.connect(database_file)
        except Error as error:
            print(error)

    def close_connection(self):
        """
        Close database connection
        """
        self.connection.close()

    def get_user_data(self, login_number):
        """
        Query user password from user table
        Arguments:
            login_number: user login
        Returns:
            row: tuple with result
        """
        try:
            cursor = self.connection.cursor()
            query = '''SELECT password FROM user WHERE login=?'''
            cursor.execute(query, (login_number,))
            row = cursor.fetchone()

            return row
        except Error as error:
            print("Failed to read data from sqlite table", error)

    def get_voter_status(self, table, registration):
        """
        Query voter status from voter table
        Arguments:
            table: name of db table
            registration: registration number of voter
        Returns:
            row: tuple with result
        """
        try:
            cursor = self.connection.cursor()
            query = '''SELECT status FROM {} WHERE registration_number=?'''.format(table)
            cursor.execute(query, (registration,))
            row = cursor.fetchone()

            return row
        except Error as error:
            print("Failed to read data from sqlite table", error)

    def set_voter_status(self, table, registration):
        """
        Update voter status in voter table
        Arguments:
            table: name of db table
            registration: registration number of voter
        """
        try:
            sql = '''UPDATE {} SET status=? WHERE registration_number=?'''.format(table)
            cursor = self.connection.cursor()
            cursor.execute(sql, (4, registration,))
            self.connection.commit()
        except Error as error:
            print("Failed to read data from sqlite table", error)

    def get_candidate(self, candidate_type, candidate_chosen):
        """
        Query candidate info from candidate table
        Arguments:
            candidate_type: position that candidate is running for
            candidate_chosen: political number of candidate
        Returns:
            row: tuple with result
        """
        try:
            cursor = self.connection.cursor()
            query = '''SELECT name, political_party FROM {}_candidate
                    WHERE number=?'''.format(candidate_type.lower())
            cursor.execute(query, (candidate_chosen,))
            row = cursor.fetchone()

            return row
        except Error as error:
            print("Failed to read data from sqlite table", error)

    def set_voter_choice(self, candidate_type, candidate_chosen):
        """
        Update the vote count with the voter's vote, i.e., increment
        the number of votes for the chosen candidate by 1
        Arguments:
            candidate_type: position that candidate is running for
            candidate_chosen: political number of candidate
        """
        try:
            sql = '''UPDATE {}_voting_result SET number_of_votes=number_of_votes + 1
                    WHERE candidate_number=?'''.format(candidate_type.lower())
            cursor = self.connection.cursor()
            cursor.execute(sql, (candidate_chosen,))
            self.connection.commit()
        except Error as error:
            print("Failed to read data from sqlite table", error)

    def get_vote_count(self, candidate_type):
        """
        Query vote count from candidate_type_voting_result table
        Arguments:
            candidate_type: position that candidate is running for
        Returns:
            row: tuple with result
        """
        try:
            cursor = self.connection.cursor()
            query = '''SELECT name, number_of_votes
                    FROM {}_voting_result'''.format(candidate_type.lower())
            cursor.execute(query)
            row = cursor.fetchall()

            return row
        except Error as error:
            print("Failed to read data from sqlite table", error)

    def get_candidate_vote_count(self, candidate_type, candidate_number):
        """
        Query vote count from a specific candidate in
        candidate_type_voting_result table
        Arguments:
            candidate_type: position that candidate is running for
        Returns:
            row: tuple with result
        """
        try:
            cursor = self.connection.cursor()
            query = '''SELECT name, number_of_votes
                    FROM {}_voting_result
                    WHERE candidate_number=?'''.format(candidate_type.lower())
            cursor.execute(query, (candidate_number,))
            row = cursor.fetchone()

            return row
        except Error as error:
            print("Failed to read data from sqlite table", error)

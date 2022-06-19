import sqlite3
from sqlite3 import Error

class AccessDB:
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
    
    def get_voter_status(self, table, system_query):
        """
        Query voter status from voter table
        Arguments:
            query: voter condition
        Returns:
            rows: tuple
        """
        try:
            cursor = self.connection.cursor()
            query = '''SELECT status FROM {} WHERE registration_number=?'''.format(table)
            cursor.execute(query, (system_query,))
            rows = cursor.fetchone()

            return rows
        except Error as error:
            print("Failed to read data from sqlite table", error)
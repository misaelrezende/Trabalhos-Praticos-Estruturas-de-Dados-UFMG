import sqlite3
from sqlite3 import Error

sql_create_voter_table = """CREATE TABLE IF NOT EXISTS voter (
    registration_number integer PRIMARY KEY,
    name text NOT NULL,
    status integer NOT NULL,
    pooling_station integer NOT NULL
);"""

sql_create_president_candidate_table = """CREATE TABLE IF NOT EXISTS presidente_candidate (
	number integer PRIMARY KEY,
	name text NOT NULL,
    political_party text NOT NULL
);"""
sql_create_senator_candidate_table = """CREATE TABLE IF NOT EXISTS senador_candidate (
	number integer PRIMARY KEY,
	name text NOT NULL,
    political_party text NOT NULL
);"""

sql_create_president_voting_resulting_table = """CREATE TABLE IF NOT EXISTS presidente_voting_result (
    id integer PRIMARY KEY,
	candidate_number integer NOT NULL,
	name text NOT NULL,
	number_of_votes integer NOT NULL
);"""
sql_create_senator_voting_resulting_table = """CREATE TABLE IF NOT EXISTS senador_voting_result (
    id integer PRIMARY KEY,
	candidate_number integer NOT NULL,
	name text NOT NULL,
	number_of_votes integer NOT NULL
);"""

sql_create_user_table = """CREATE TABLE IF NOT EXISTS user (
    id integer PRIMARY KEY,
    login integer NOT NULL,
    password text NOT NULL
    );"""

class CreateDB:
    def __init__(self, db_path = "src/db/voting_system.db"):
        self.connection = None
        self.database_file = db_path
        self.create_connection(self.database_file)

    def create_connection(self, database_file):
        """
        Create a database connection to a SQLite database
        :param database_file: database file
        """
        try:
            self.connection = sqlite3.connect(database_file)
        except Error as e:
            print(e)

    def create_table(self, create_table_sql):
        """
        Create a table from the create_table_sql statement
        :param create_table_sql: a CREATE TABLE statement
        """
        try:
            cursor = self.connection.cursor()
            cursor.execute(create_table_sql)
        except Error as e:
            print(e)

    def create_voter(self, voter):
        """
        Create a new voter into the voter table
        :param voter: tuple of data
        :return: voter id
        """
        sql = ''' INSERT OR REPLACE INTO voter(registration_number,name,status,pooling_station)
                VALUES(?,?,?,?) '''
        cursor = self.connection.cursor()
        cursor.execute(sql, voter)
        self.connection.commit()
        return cursor.lastrowid
    
    def create_candidate(self, candidate, occupation):
        """
        Create a new candidate into the candidate table
        :param candidate: tuple of data
        :param occupation: occupation of candidate
        :return: candidate id
        """
        sql = ''' INSERT OR REPLACE INTO {}_candidate(number,name,political_party)
                VALUES(?,?,?) '''.format(occupation)
        cursor = self.connection.cursor()
        cursor.execute(sql, candidate)
        self.connection.commit()
        return cursor.lastrowid

    def create_voting_results_table(self, candidate, occupation):
        """
        Create a new candidate into the candidate table
        :param candidate: tuple of data
        :param occupation: occupation of candidate
        :return: candidate id
        """
        sql = ''' INSERT OR REPLACE INTO {}_voting_result(id,candidate_number,name,number_of_votes)
                VALUES(?,?,?,?) '''.format(occupation)
        cursor = self.connection.cursor()
        cursor.execute(sql, candidate)
        self.connection.commit()
        return cursor.lastrowid

    def create_user(self, user):
        """
        Create a new user into the user table
        :param user: tuple of data
        :return: user id
        """
        sql = ''' INSERT OR REPLACE INTO user(id,login,password)
                VALUES(?,?,?) '''
        cursor = self.connection.cursor()
        cursor.execute(sql, user)
        self.connection.commit()
        return cursor.lastrowid

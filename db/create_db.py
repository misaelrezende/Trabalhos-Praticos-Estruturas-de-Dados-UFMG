import sqlite3
from sqlite3 import Error

sql_create_voter_table = """CREATE TABLE IF NOT EXISTS voter (
    registration_number integer PRIMARY KEY,
    name text NOT NULL,
    status integer NOT NULL,
    pooling_station integer NOT NULL
);"""

sql_create_president_candidate_table = """CREATE TABLE IF NOT EXISTS president_candidate (
	number integer PRIMARY KEY,
	name text NOT NULL,
    political_party text NOT NULL
);"""
sql_create_senator_candidate_table = """CREATE TABLE IF NOT EXISTS senator_candidate (
	number integer PRIMARY KEY,
	name text NOT NULL,
    political_party text NOT NULL
);"""

sql_create_president_voting_resulting_table = """CREATE TABLE IF NOT EXISTS president_voting_result (
    id integer PRIMARY KEY,
	candidate_number integer NOT NULL,
	name text NOT NULL,
	number_of_votes integer NOT NULL
);"""
sql_create_senator_voting_resulting_table = """CREATE TABLE IF NOT EXISTS senator_voting_result (
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
    def __init__(self, database_file):
        self.connection = None
        self.create_connection(database_file)

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
        sql = ''' INSERT INTO voter(registration_number,name,status,pooling_station)
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
        sql = ''' INSERT INTO {}_candidate(number,name,political_party)
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
        sql = ''' INSERT INTO {}_voting_result(id,candidate_number,name,number_of_votes)
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
        sql = ''' INSERT INTO user(id,login,password)
                VALUES(?,?,?) '''
        cursor = self.connection.cursor()
        cursor.execute(sql, user)
        self.connection.commit()
        return cursor.lastrowid

# Create Database
db = CreateDB("voting_system.db")

db.create_table(sql_create_voter_table)
db.create_table(sql_create_president_candidate_table)
db.create_table(sql_create_senator_candidate_table)
db.create_table(sql_create_president_voting_resulting_table)
db.create_table(sql_create_senator_voting_resulting_table)
db.create_table(sql_create_user_table)

users = [(1, 123456, '123456')]

for user in users:
    db.create_user(user)

voters = [(1234567891011, "Conceição Evaristo", 1, 123),
          (4567891011123, "Graciliano Ramos", 4, 456),
          (7891011121314, "Joaquim Maria Machado de Assis", 4, 123)
          ]

for voter in voters:
    db.create_voter(voter)

president_candidates = [(13, 'Luiz Inácio Lula da Silva', 'PT'), 
            (22, 'Jair Messias Bolsonaro', 'PL'),
            (12, 'Ciro Gomes', 'PDT'),
            (15, 'Simone Nassar Tebet', 'MDB')
            ]

senator_candidates = [(451, 'Aécio Neves', 'PSDB'),
            (202, 'Cleitinho', 'PSC'),
            (553, 'Alexandre Silveira', 'PSD'),
            (124, 'Duda Salabert', 'PDT')
            ]

president_voting_results = [(1, 13, 'Luiz Inácio Lula da Silva', 0), 
            (2, 22, 'Jair Messias Bolsonaro', 0),
            (3, 12, 'Ciro Gomes', 0),
            (4, 15, 'Simone Nassar Tebet', 0),
            (5, 0, 'Nulo', 0)
            ]

senator_voting_results = [(1, 451, 'Aécio Neves', 0),
            (2, 202, 'Cleitinho', 0),
            (3, 553, 'Alexandre Silveira', 0),
            (4, 124, 'Duda Salabert', 0),
            (5, 0, 'Nulo', 0)
            ]

for candidate in president_candidates:
    db.create_candidate(candidate, 'President')

for candidate in senator_candidates:
    db.create_candidate(candidate, 'Senator')

for candidate in president_voting_results:
    db.create_voting_results_table(candidate, 'President')

for senator in senator_voting_results:
    db.create_voting_results_table(senator, 'Senator')
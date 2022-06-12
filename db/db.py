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

# sql_create_voting_resulting_table = """CREATE TABLE IF NOT EXISTS voting_result (

# 	candidate_number integer NOT NULL,
# 	name text NOT NULL,
# 	number_of_votes integer NOT NULL,
# 	FOREIGN KEY (candidate_number) REFERENCES candidate (number)
# );"""

class Database:
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


# Test Database
db = Database("pythonsqlite.db")

db.create_table(sql_create_voter_table)
db.create_table(sql_create_president_candidate_table)
db.create_table(sql_create_senator_candidate_table)

voter = (1234567891011, 'Missandei', 1, 456)
voter_id = db.create_voter(voter)

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

for candidate in president_candidates:
    db.create_candidate(candidate, 'President')

for candidate in senator_candidates:
    db.create_candidate(candidate, 'Senator')
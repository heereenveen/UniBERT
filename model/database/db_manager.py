import psycopg2
from model.config import DB_CONFIG

class DatabaseManager:
    def __init__(self):
        self.connection = psycopg2.connect(**DB_CONFIG)
        
    def get_contexts(self):
        cursor = self.connection.cursor()
        cursor.execute("SELECT context FROM contexts")
        return cursor.fetchall()
        
    def get_qa_pairs(self):
        cursor = self.connection.cursor()
        cursor.execute("SELECT question, answer FROM qa_pairs")
        return cursor.fetchall()
        
    def insert_context(self, context):
        cursor = self.connection.cursor()
        cursor.execute(
            "INSERT INTO contexts (context) VALUES (%s) RETURNING id",
            (context,)
        )
        self.connection.commit()
        return cursor.fetchone()[0]
        
    def insert_qa_pair(self, context_id, question, answer, answer_start):
        cursor = self.connection.cursor()
        cursor.execute(
            """INSERT INTO qa_pairs 
            (context_id, question, answer, answer_start) 
            VALUES (%s, %s, %s, %s)""",
            (context_id, question, answer, answer_start)
        )
        self.connection.commit()

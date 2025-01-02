import sqlite3


class DatabaseManager:
    def __init__(self):
        self.connection = sqlite3.connect("data/fiot_qa.db")
        self.create_tables()

    def create_tables(self):
        cursor = self.connection.cursor()
        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS contexts (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                context TEXT NOT NULL
            )
        """
        )
        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS qa_pairs (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                context_id INTEGER,
                question TEXT NOT NULL,
                answer TEXT NOT NULL,
                answer_start INTEGER,
                FOREIGN KEY (context_id) REFERENCES contexts(id)
            )
        """
        )
        self.connection.commit()

    def get_contexts(self):
        cursor = self.connection.cursor()
        cursor.execute("SELECT context FROM contexts")
        return cursor.fetchall()

    def get_qa_pairs(self):
        cursor = self.connection.cursor()
        cursor.execute("SELECT question, answer FROM qa_pairs")
        return cursor.fetchall()

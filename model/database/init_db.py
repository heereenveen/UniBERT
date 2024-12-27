import os
import json
import sqlite3
from model.config import DB_PATH

def init_database():
    os.makedirs('data', exist_ok=True)
    
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS contexts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            context TEXT NOT NULL
        )
    ''')
    
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS qa_pairs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            context_id INTEGER,
            question TEXT NOT NULL,
            answer TEXT NOT NULL,
            answer_start INTEGER,
            FOREIGN KEY (context_id) REFERENCES contexts(id)
        )
    ''')
    
    with open('data/fiot_data.json', 'r', encoding='utf-8') as file:
        data = json.load(file)
        
    for paragraph in data['data'][0]['paragraphs']:
        cursor.execute('INSERT INTO contexts (context) VALUES (?)', (paragraph['context'],))
        context_id = cursor.lastrowid
        
        for qa in paragraph['qas']:
            cursor.execute('''
                INSERT INTO qa_pairs (context_id, question, answer, answer_start)
                VALUES (?, ?, ?, ?)
            ''', (context_id, qa['question'], qa['answers'][0]['text'], qa['answers'][0]['answer_start']))
    
    conn.commit()
    conn.close()
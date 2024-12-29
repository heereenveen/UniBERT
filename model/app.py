from flask import Flask, request, jsonify
from evaluation import answer_question
from database.init_db import init_database
import os
from config import DB_PATH

app = Flask(__name__)

if not os.path.exists(DB_PATH):
    init_database()
    
@app.route('/BERT/answer', methods=['POST'])
def get_answer():
    try:
        data = request.get_json()
        if not data or 'question' not in data:
            return jsonify({'error': 'Необхідно надати питання'}), 400
        
        question = data['question']
        answer = answer_question(question)
        return jsonify({'answer': answer})
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
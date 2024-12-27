from flask import Flask, request, jsonify
from model.evaluation import answer_question
from model.train import train_model
from transformers import AutoTokenizer, AutoModelForQuestionAnswering
from model.config import MODEL_NAME, MODEL_DIR
import os

app = Flask(__name__)

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

@app.route('/BERT/train', methods=['POST'])
def start_training():
    try:
        if not os.path.exists(MODEL_DIR):
            print("Тренування нової моделі...")
            model, tokenizer = train_model()
            if model and tokenizer:
                model.save_pretrained(MODEL_DIR)
                tokenizer.save_pretrained(MODEL_DIR)
                return jsonify({'message': 'Модель успішно навчена та збережена'})
            else:
                return jsonify({'error': 'Помилка тренування моделі'}), 500
        else:
            return jsonify({'message': 'Модель вже існує'})
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    if not os.path.exists(MODEL_DIR):
        print("Initializing model...")
        tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
        model = AutoModelForQuestionAnswering.from_pretrained(MODEL_NAME)
        train_model()
    
    app.run(host='0.0.0.0', port=5000)
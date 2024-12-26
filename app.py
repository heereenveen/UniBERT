from flask import Flask, request, jsonify
from model.evaluation import evaluate_model
from model.train import train_model

app = Flask(__name__)

@app.route('/BERT/answer', methods=['POST'])
def get_answer():
    try:
        data = request.get_json()
        if not data or 'question' not in data or 'context' not in data:
            return jsonify({'error': 'Необхідно надати питання та контекст'}), 400
        
        question = data['question']
        context = data['context']
        
        answer = evaluate_model(question, context)
        return answer
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@app.route('/BERT/train', methods=['POST'])
def start_training():
    try:
        train_model()
        return jsonify({'message': 'Модель успішно навчена'})
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

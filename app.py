from flask import Flask, request, jsonify
from model.evaluation import answer_question

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

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
from transformers import pipeline
from config import MODEL_DIR
from database.db_manager import DatabaseManager

def answer_question(question: str):
    qa_pipeline = pipeline(
        "question-answering", 
        model=MODEL_DIR,
        tokenizer=MODEL_DIR,
        handle_impossible_answer=True
    )
    
    db = DatabaseManager()
    contexts = db.get_contexts()
    qa_pairs = db.get_qa_pairs()

    for qa in qa_pairs:
        if question.lower() == qa[0].lower():
            return qa[1]

    answers = []
    for context in contexts:
        try:
            result = qa_pipeline(
                question=question,
                context=context[0],
                max_answer_len=200,
                handle_impossible_answer=True,
                top_k=1
            )
            if result['score'] > 0.3:
                answers.append({
                    'answer': result['answer'],
                    'score': result['score'],
                    'context': context[0]
                })
        except Exception as e:
            continue

    if not answers:
        return "Вибачте, я не можу знайти відповідь на це питання"

    best_answer = max(answers, key=lambda x: x['score'])
    return best_answer['answer']
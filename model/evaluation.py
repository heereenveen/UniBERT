from transformers import pipeline
from model.config import MODEL_DIR
from model.data_preparation import load_dataset

def answer_question(question: str):
    qa_pipeline = pipeline(
        "question-answering", 
        model=MODEL_DIR,
        tokenizer=MODEL_DIR,
        handle_impossible_answer=True
    )
    
    paragraphs = load_dataset()
    if not paragraphs:
        return "Помилка завантаження даних"

    for paragraph in paragraphs:
        for qa in paragraph["qas"]:
            if question.lower() == qa["question"].lower():
                return qa["answers"][0]["text"]

    answers = []
    for paragraph in paragraphs:
        try:
            result = qa_pipeline(
                question=question,
                context=paragraph["context"],
                max_answer_len=200,
                handle_impossible_answer=True,
                top_k=1
            )
            if result['score'] > 0.3:
                answers.append({
                    'answer': result['answer'],
                    'score': result['score'],
                    'context': paragraph["context"]
                })
        except Exception as e:
            continue

    if not answers:
        return "Вибачте, я не можу знайти відповідь на це питання"

    best_answer = max(answers, key=lambda x: x['score'])
    return best_answer['answer']
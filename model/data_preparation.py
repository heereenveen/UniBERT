from model.config import DB_PATH
import sqlite3

def load_dataset():
    try:
        connection = sqlite3.connect(DB_PATH)
        cursor = connection.cursor()
        
        cursor.execute("""
            SELECT c.context, q.question, q.answer, q.answer_start 
            FROM contexts c 
            JOIN qa_pairs q ON c.id = q.context_id
        """)
        
        paragraphs = []
        current_context = None
        current_qas = []
        
        for row in cursor.fetchall():
            context, question, answer, answer_start = row
            
            if current_context != context:
                if current_context is not None:
                    paragraphs.append({
                        "context": current_context,
                        "qas": current_qas
                    })
                current_context = context
                current_qas = []
            
            current_qas.append({
                "question": question,
                "answers": [{
                    "text": answer,
                    "answer_start": answer_start
                }]
            })
        
        if current_context is not None:
            paragraphs.append({
                "context": current_context,
                "qas": current_qas
            })
            
        connection.close()
        return paragraphs
        
    except sqlite3.Error as e:
        print(f"Помилка при роботі з базою даних: {str(e)}")
        return None
    except Exception as e:
        print(f"Виникла помилка при завантаженні даних: {str(e)}")
        return None

def preprocess_data(batch, tokenizer):
    contexts = []
    questions = []
    start_positions = []
    end_positions = []

    for paragraph in batch["paragraphs"]:
        context = paragraph["context"]
        for qa in paragraph["qas"]:
            question = qa["question"]
            answer = qa["answers"][0]
            start_char = answer["answer_start"]
            answer_text = answer["text"]
            end_char = start_char + len(answer_text)

            tokenized_context = tokenizer(
                context,
                question,
                truncation=True,
                max_length=180,
                padding="max_length",
                return_offsets_mapping=True,
                return_tensors="pt"
            )

            offsets = tokenized_context.pop("offset_mapping")
            start_token = None
            end_token = None

            for idx, (start, end) in enumerate(offsets[0]):
                if start <= start_char < end:
                    start_token = idx
                if start < end_char <= end:
                    end_token = idx
                    break

            contexts.append(context)
            questions.append(question)
            start_positions.append(start_token if start_token is not None else 0)
            end_positions.append(end_token if end_token is not None else 0)

    tokenized_data = tokenizer(
        contexts,
        questions,
        truncation=True,
        padding="max_length",
        max_length=512,
    )

    tokenized_data["start_positions"] = start_positions
    tokenized_data["end_positions"] = end_positions

    return tokenized_data

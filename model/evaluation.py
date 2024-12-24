from transformers import pipeline
from model.config import MODEL_DIR

def evaluate_model(question, context):
    qa_pipeline = pipeline("question-answering", model=MODEL_DIR, tokenizer=MODEL_DIR, device=0)
    result = qa_pipeline(question=question, context=context)
    return result["answer"]
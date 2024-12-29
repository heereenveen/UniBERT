from transformers import AutoTokenizer, AutoModelForQuestionAnswering, TrainingArguments, Trainer
from datasets import Dataset
from config import MODEL_NAME, TRAINING_ARGS
from data_preparation import load_dataset, preprocess_data

def train_model():
    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForQuestionAnswering.from_pretrained(MODEL_NAME)

    paragraphs = load_dataset()
    if not paragraphs:
        return None, None

    dataset = Dataset.from_dict({"paragraphs": paragraphs})
    tokenized_dataset = dataset.map(
        lambda x: preprocess_data(x, tokenizer), 
        batched=True, 
        remove_columns=["paragraphs"]
    )

    training_args = TrainingArguments(**TRAINING_ARGS)

    trainer = Trainer(
        model=model,
        args=training_args,
        train_dataset=tokenized_dataset
    )

    trainer.train()
    return model, tokenizer
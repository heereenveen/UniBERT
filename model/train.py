from transformers import Trainer, TrainingArguments, AutoModelForQuestionAnswering, AutoTokenizer
from datasets import Dataset
from model.data_preparation import preprocess_data, load_full_dataset
from model.config import MODEL_NAME, TRAINING_ARGS

def train_model():
    raw_data = {"paragraphs": load_full_dataset()}
    dataset = Dataset.from_dict(raw_data)

    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForQuestionAnswering.from_pretrained(MODEL_NAME)

    print("Data tokenization...")
    tokenized_dataset = dataset.map(lambda x: preprocess_data(x, tokenizer), batched=True)

    print("Training model...")
    training_args = TrainingArguments(**TRAINING_ARGS)
    trainer = Trainer(
        model=model,
        args=training_args,
        train_dataset=tokenized_dataset,
        tokenizer=tokenizer
    )

    trainer.train()
    model.save_pretrained(TRAINING_ARGS["output_dir"])
    tokenizer.save_pretrained(TRAINING_ARGS["output_dir"])
    print("Model was trained and saved!")

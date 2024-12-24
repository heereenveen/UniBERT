import json
from model.config import INPUT_FILE

def load_full_dataset():
    with open(INPUT_FILE, "r", encoding="utf-8") as file:
        data = json.load(file)["data"]
    paragraphs = []
    for item in data:
        paragraphs.extend(item["paragraphs"])
    return paragraphs

def preprocess_data(batch, tokenizer):
    contexts, questions = [], []
    start_positions, end_positions = [], []

    for paragraph in batch["paragraphs"]:
        context = paragraph["context"]
        for qa in paragraph["qas"]:
            question = qa["question"]
            answer = qa["answers"][0]
            start_char = answer["answer_start"]
            end_char = start_char + len(answer["text"])

            tokenized_context = tokenizer(
                context,
                question,
                truncation="only_second",
                max_length=512,
                padding="max_length",
                return_offsets_mapping=True,
            )

            offsets = tokenized_context.pop("offset_mapping")
            start_token, end_token = None, None
            for idx, (start, end) in enumerate(offsets):
                if start <= start_char < end:
                    start_token = idx
                if start < end_char <= end:
                    end_token = idx

            if start_token is None or end_token is None:
                start_token = tokenizer.model_max_length
                end_token = tokenizer.model_max_length

            contexts.append(context)
            questions.append(question)
            start_positions.append(start_token)
            end_positions.append(end_token)

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
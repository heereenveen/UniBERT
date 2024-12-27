import os

DATA_DIR = os.path.join("data")
MODEL_DIR = os.path.join(DATA_DIR, "fiot_bert_model")
INPUT_FILE = os.path.join(DATA_DIR, "fiot_data.json")
MODEL_NAME = "bert-base-multilingual-uncased"

TRAINING_ARGS = {
    "output_dir": "./results",
    "learning_rate": 5e-5,
    "per_device_train_batch_size": 16,
    "num_train_epochs": 50,
    "weight_decay": 0.01,
    "logging_dir": "./logs",
    "logging_steps": 10,
    "fp16": True,
    "report_to": "none"
}

MAX_LENGTH = 512
TRUNCATION = True
PADDING = "max_length"

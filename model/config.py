import os

DATA_DIR = os.path.join("data")
MODEL_DIR = os.path.join(DATA_DIR, "fiot_bert_model")

INPUT_FILE = os.path.join(DATA_DIR, "fiot_data.json")

MODEL_NAME = "bert-base-multilingual-cased"

TRAINING_ARGS = {
    "output_dir": "./results",
    "evaluation_strategy": "no",
    "save_strategy": "epoch",
    "learning_rate": 1e-5,
    "per_device_train_batch_size": 4,
    "num_train_epochs": 20,
    "weight_decay": 0.01,
    "logging_dir": "./logs",
    "logging_steps": 10,
    "fp16": True,
}
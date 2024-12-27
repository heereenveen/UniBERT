CREATE TABLE contexts (
    id SERIAL PRIMARY KEY,
    context TEXT NOT NULL
);

CREATE TABLE qa_pairs (
    id SERIAL PRIMARY KEY,
    context_id INTEGER REFERENCES contexts(id),
    question TEXT NOT NULL,
    answer TEXT NOT NULL,
    answer_start INTEGER,
    FOREIGN KEY (context_id) REFERENCES contexts(id)
);
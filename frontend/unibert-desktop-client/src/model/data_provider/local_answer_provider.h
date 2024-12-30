#ifndef LOCAL_ANSWER_PROVIDER_H
#define LOCAL_ANSWER_PROVIDER_H

#include "answers_provider_i.h"

// this is the class, which will give answers
// from local storage - in my case, probably from some static vector

class LocalAnswerProvider : public AnswersProvider_I {
 public:
  LocalAnswerProvider() = default;
  virtual ~LocalAnswerProvider() override = default;

 public:
  virtual std::string GetAnswer(const std::string& question) override;
};

#endif  //LOCAL_ANSWER_PROVIDER_H

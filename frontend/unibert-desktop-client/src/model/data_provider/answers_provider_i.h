#ifndef DATA_SUPPLIER_H
#define DATA_SUPPLIER_H
#include <string>

class AnswersProvider_I {
 public:
  AnswersProvider_I() = default;
  virtual ~AnswersProvider_I() = default;

 public:
  virtual std::string GetAnswer(const std::string& question) = 0;
};

#endif  //DATA_SUPPLIER_H

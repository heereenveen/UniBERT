#ifndef SERVER_ANSWER_SUPPLIER_H
#define SERVER_ANSWER_SUPPLIER_H

#include <memory>

#include "answers_provider_i.h"

class HttpClient_I;
class ServerAnswerSupplier : public AnswersProvider_I {
 public:
  explicit ServerAnswerSupplier(
      const std::shared_ptr<HttpClient_I>& httpClient);
  virtual ~ServerAnswerSupplier() override = default;

 public:
  void SetHttpClient(const std::shared_ptr<HttpClient_I>& httpClient);

 public:
  // Note - this function is synchronous, so it WILL freeze your thread
  // please, call it wrapped in future
  virtual std::string GetAnswer(const std::string& question) override;

 protected:
  std::shared_ptr<HttpClient_I> http_client_;
};

#endif  //SERVER_ANSWER_SUPPLIER_H

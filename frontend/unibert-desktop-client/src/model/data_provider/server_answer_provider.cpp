#include "server_answer_provider.h"

#include <sstream>

#include "../network/http_client_i.h"

#include <nlohmann/json.hpp>

ServerAnswerSupplier::ServerAnswerSupplier(
    const std::shared_ptr<HttpClient_I>& httpClient) {
  SetHttpClient(httpClient);
}

void ServerAnswerSupplier::SetHttpClient(
    const std::shared_ptr<HttpClient_I>& httpClient) {
  http_client_ = httpClient;
}

std::string ServerAnswerSupplier::GetAnswer(const std::string& question) {
  nlohmann::json cookedJson = {{"question", question}};

  auto answerRawJSON =
      http_client_->SendJSONPostRequest("/BERT/answer", cookedJson.dump());

  auto answerJSON = nlohmann::json::parse(answerRawJSON);
  auto answerStr = answerJSON["answer"].get<std::string>();
  return answerStr;
}
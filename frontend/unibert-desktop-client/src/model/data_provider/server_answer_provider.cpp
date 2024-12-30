#include "server_answer_provider.h"

#include <format>
#include <sstream>

#include "../network/http_client_i.h"

ServerAnswerSupplier::ServerAnswerSupplier(
    const std::shared_ptr<HttpClient_I>& httpClient) {
  SetHttpClient(httpClient);
}

void ServerAnswerSupplier::SetHttpClient(
    const std::shared_ptr<HttpClient_I>& httpClient) {
  http_client_ = httpClient;
}

std::string ServerAnswerSupplier::GetAnswer(const std::string& question) {
  std::stringstream cookedJson;
  cookedJson << "{\n";
  cookedJson << R"( "question": )";
  cookedJson << '"' << question << '"';
  cookedJson << "\n}";

  auto answerRaw =  http_client_->SendJSONPostRequest("/BERT/answer", cookedJson.str());

  return answerRaw;
}
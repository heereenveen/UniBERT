#include "server_answer_provider.h"

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
  return http_client_->SendEmptyGetRequest(question);
}
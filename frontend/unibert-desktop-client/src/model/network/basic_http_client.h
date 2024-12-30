#ifndef BASIC_HTTP_CLIENT_H
#define BASIC_HTTP_CLIENT_H

#include <future>
#include <sstream>
#include <string>
#include <vector>

#include "http_client_i.h"

class BasicHttpClient : public HttpClient_I {
 public:
  // we set base url,
  // relative to which all requests with custom routes will go
  BasicHttpClient() = default;
  virtual ~BasicHttpClient() override = default;

 public:
  virtual void SetInitData(const HttpInitData& init_data) override;

 public:
  virtual std::string SendEmptyGetRequest(
      const std::string& route = "") override;

  virtual std::string SendJSONPostRequest(const std::string& route,
                                          const std::string& json) override;

 protected:
  std::string url_;
  int port_;
};

#endif  //BASIC_HTTP_CLIENT_H

#ifndef HTTP_CLIENT_I_H
#define HTTP_CLIENT_I_H

struct HttpInitData {
  std::string base_url = "localhost";
  int port = 80;
};

class HttpClient_I {
 public:
  HttpClient_I() = default;
  virtual ~HttpClient_I() = default;

 public:
  virtual void SetInitData(const HttpInitData& init_data) = 0;

 public:
  // that's the route relative to base url
  virtual std::string SendEmptyGetRequest(const std::string& route) = 0;
  virtual std::string  SendJSONPostRequest(const std::string& route, const std::string& json) = 0;
};

#endif  //HTTP_CLIENT_I_H

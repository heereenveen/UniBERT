#ifndef BASIC_HTTP_CLIENT_H
#define BASIC_HTTP_CLIENT_H

#include <future>
#include <sstream>
#include <string>
#include <vector>

class BasicHttpClient {
 public:
  // we set base url,
  // relative to which all requests with custom routes will go
  explicit BasicHttpClient(const std::string& base_url = "localhost",
                           int port = 80);
  ~BasicHttpClient();

 public:
  std::future<std::string> SendEmptyGetRequest(const std::string& route = "");

  using PostHeaderData = std::vector<std::pair<std::string, std::string>>;
  // std::future<std::string> SendPostRequest(const std::string& route = "",
  //                                          const PostHeaderData& post_header_data);

 protected:
  std::string url_;
  int port_;
};

#endif  //BASIC_HTTP_CLIENT_H

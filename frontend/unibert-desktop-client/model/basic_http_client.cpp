#include "basic_http_client.h"

#include <unistd.h>
#include <cstring>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <future>
#include <sstream>

BasicHttpClient::BasicHttpClient(const std::string& base_url, int port)
    : url_(base_url), port_(port) {}

BasicHttpClient::~BasicHttpClient() = default;

std::future<std::string> BasicHttpClient::SendEmptyGetRequest(
    const std::string& route) {
  using namespace curlpp;

  auto request_fn = [route, url = url_, port = port_] {
    std::stringstream response;
    try {
      // preparing request to be sent.
      Easy myRequest;

      std::vector<OptionBase*> options;

      options.push_back(new options::Url(url + route));
      options.push_back(new options::Port(port));
      options.push_back(new options::WriteStream(&response));

      myRequest.setOpt(options.begin(), options.end());

      myRequest.perform();
    }

    catch (RuntimeError& e) {
      std::cout << e.what() << std::endl;
    }

    catch (LogicError& e) {
      std::cout << e.what() << std::endl;
    }
    // sleep(1);
    return response.str();
  };

  auto future = std::async(std::launch::async, request_fn);
  return future;
}

// std::future<std::string> BasicHttpClient::SendPostRequest(const std::string &route,
//                                                           const PostHeaderData& post_header_data_) {
//
// }

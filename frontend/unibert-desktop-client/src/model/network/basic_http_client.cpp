#include "basic_http_client.h"

#include <unistd.h>
#include <cstring>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <future>
#include <sstream>

std::string BasicHttpClient::SendEmptyGetRequest(const std::string& route) {
  using namespace curlpp;

  std::stringstream response;
  try {
    // preparing request to be sent.
    Easy myRequest;

    std::vector<OptionBase*> options;

    options.push_back(new options::Url(url_ + route));
    options.push_back(new options::Port(port_));
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

  return response.str();
}

std::string BasicHttpClient::SendJSONPostRequest(const std::string& route,
                                                 const std::string& json) {
  using namespace curlpp;

  std::stringstream response;
  try {
    // preparing request to be sent.
    Easy myRequest;

    std::vector<OptionBase*> options;

    options.push_back(new options::Url(url_ + route));
    options.push_back(new options::Port(port_));
    options.push_back(
        new curlpp::options::HttpHeader({"Content-Type: application/json"}));
    options.push_back(new curlpp::options::Post(true));  // Set POST request
    options.push_back(
        new curlpp::options::PostFields(json));  // Set the JSON body
    options.push_back(new curlpp::options::PostFieldSize(
        json.size()));  // Set the size of the JSON body

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

  return response.str();
}

void BasicHttpClient::SetInitData(const HttpInitData& init_data) {
  url_ = init_data.base_url;
  port_ = init_data.port;
}
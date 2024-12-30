#include "local_answer_provider.h"

#include <unistd.h>

#include <map>
#include <ranges>

static std::map<std::string, std::string> local_answers_map = {
    {"foo", "bar"},
    {"Dmytro Nechai is", "our beloved teacher"},
    {"please", "give us 60 balls"},
};

std::string LocalAnswerProvider::GetAnswer(const std::string& question) {
  sleep(12);
  auto it = local_answers_map.find(question);
  if (it == local_answers_map.end()) {
    return "no answer(";
  } else {
    return it->second;
  }
}

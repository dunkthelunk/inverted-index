#ifndef UTIL_TOKENIZER_H
#define UTIL_TOKENIZER_H

#include <map>
#include <set>
#include <string>
#include <vector>

class Tokenizer {
public:
  virtual std::vector<std::string> *tokenize(const std::string &Text) = 0;
  virtual std::map<std::string, std::set<unsigned int>>
  tokenize2(const std::string &Text) = 0;
};

#endif

#include "split.h"

std::vector<std::string> SplitString(const std::string &str) {
  std::istringstream iss(str);

  return {std::istream_iterator<std::string>(iss),
          std::istream_iterator<std::string>()};
}

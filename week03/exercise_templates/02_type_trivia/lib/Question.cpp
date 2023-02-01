#include "Question.hpp"

#include <algorithm>
#include <cctype>
#include <string>

namespace TypeTrivia {

namespace {

auto compareWhitespaceless(std::string const& first, std::string const& second)
    -> bool {
  std::string whitespacelessFirst{first}, whitespacelessSecond{second};
  whitespacelessFirst.erase(
      std::remove_if(whitespacelessFirst.begin(), whitespacelessFirst.end(),
                     ::isspace),
      whitespacelessFirst.end());
  whitespacelessSecond.erase(
      std::remove_if(whitespacelessSecond.begin(), whitespacelessSecond.end(),
                     ::isspace),
      whitespacelessSecond.end());
  return whitespacelessFirst == whitespacelessSecond;
}
}  // namespace

auto Question::checkTypeT(std::string const& answer) const -> bool {
  return compareWhitespaceless(answer, typeT);
}

auto Question::checkTypeP(std::string const& answer) const -> bool {
  return compareWhitespaceless(answer, typeParamType);
}

}  // namespace TypeTrivia
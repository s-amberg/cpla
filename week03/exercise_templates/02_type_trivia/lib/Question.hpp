
#ifndef QUESTION_HPP_
#define QUESTION_HPP_

#include <string>

namespace TypeTrivia {

struct Question {
  [[nodiscard]] auto checkTypeT(std::string const& answer) const -> bool;
  [[nodiscard]] auto checkTypeP(std::string const& answer) const -> bool;

  std::string callingCode;
  std::string calledCode;
  std::string typeT;
  std::string typeParamType;
};

}  // namespace TypeTrivia

#endif /* QUESTION_HPP_ */

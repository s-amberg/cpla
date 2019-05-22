#include "frobnify.h"

#include <sstream>

std::string frobnify(std::string input)
  {
  std::ostringstream buffer{};
  auto cow_marker = input.find("cow");

  buffer << input.substr(0, cow_marker)
         << "cowoidal animal"
         << input.substr(cow_marker + 3, std::string::npos);

  return buffer.str();
  }

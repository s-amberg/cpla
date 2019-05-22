#include "discombobulate.h"

#include <algorithm>
#include <array>

constexpr std::array<char, 3> end_markers{'.', '?', '!'};

std::string discombobulate(std::string input)
  {
  auto has_end_marker = std::find(end_markers.begin(), end_markers.end(), input.back()) != end_markers.end();
  if(has_end_marker)
    {
    input = input.substr(0, input.length() - 1);
    }

  return input + "... " + "Whait... WHAT?!";
  }


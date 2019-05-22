#include "frobnify.h"
#include "discombobulate.h"

#include <algorithm>
#include <iostream>
#include <string>

int main()
  {
  std::string input{};
  std::cout << "Please enter a sentence containing the word 'cow': ";
  std::getline(std::cin, input);

  if(input.find("cow") == std::string::npos)
    {
    std::cerr << "Your sentence did not include the word 'cow'!\n";
    return 1;
    }

  auto frobnified = frobnify(input);
  std::cout << "Your sentence after frobnification: " << frobnified << '\n';

  auto frobnibulated = discombobulate(frobnified);
  std::cout << "Your fully frobnibulated sentence: " << frobnibulated << '\n';
  }

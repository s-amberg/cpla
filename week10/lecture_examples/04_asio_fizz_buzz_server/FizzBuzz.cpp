#include "FizzBuzz.h"

#include <string>

std::string fizzbuzz(int number) {
	using namespace std::string_literals;
	std::string result { };
	if (number % 3 == 0) {
		result += "fizz"s;
	}
	if (number % 5 == 0) {
		result += "buzz"s;
	}
	if (!result.empty()) {
		return result;
	}
	return std::to_string(number);
}

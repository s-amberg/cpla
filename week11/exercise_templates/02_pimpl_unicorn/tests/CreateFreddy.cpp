#include "CreateFreddy.hpp"
#include "Unicorn.hpp"

#include <string>

auto createFreddy() -> Unicorn {
	using namespace std::string_literals;
	Unicorn freddy { "freddy"s, "red"s };
	return freddy;
}

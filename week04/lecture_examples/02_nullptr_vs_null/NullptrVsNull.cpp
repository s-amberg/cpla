#include <iostream>

struct S{};

auto bar(int i) -> void {
	std::cout << "bar(int)\n";
}

auto bar(S * ps) -> void {
	std::cout << "bar(S *)\n";
}


auto main(int argc, char **argv) -> int {
	bar(0);
//	bar(NULL);    //ambiguous
	bar(nullptr);
}

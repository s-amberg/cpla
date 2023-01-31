#include <iostream>
#include <utility>

struct S {
//	auto m() -> void {
//		std::cout << "m()\n";
//	}
//	auto m() const -> void {
//		std::cout << "m() const\n";
//	}
	auto m() & -> void {
		std::cout << "m() &\n";
	}
	auto m() const & -> void {
		std::cout << "m() const &\n";
	}
	auto m() && -> void {
		std::cout << "m() &&\n";
	}
};



auto main(int argc, char **argv) -> int {
	S s{};
	s.m();

	S const sc{};
	sc.m();

	S{}.m();

	std::move(s).m();
}

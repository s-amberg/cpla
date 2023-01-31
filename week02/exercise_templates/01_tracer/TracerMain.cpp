#include "Tracer.hpp"

auto foo(Tracer t) -> void {
	Tracer trace { "foo" };
	t.show();
}

auto bar(Tracer const &t) -> Tracer {
	Tracer trace { "bar" };
	t.show();
	return trace;
}

auto main() -> int {
	std::cout << "\n--- Tracer m{\"main\"} ---\n";
	Tracer m { "main" };
	{
		std::cout << "\n--- Tracer inner{\"inner\"} ---\n";
		Tracer inner { "inner" };
		std::cout << "\n--- foo(inner) ---\n";
		foo(inner);
		std::cout << "\n--- auto trace = bar(inner) ---\n";
		auto trace = bar(inner);
		std::cout << "\n--- tracer.show() ---\n";
		trace.show();
		std::cout << "\n--- inner.show() ---\n";
		inner.show();
		std::cout << "\n--- } ---\n";
	}
	std::cout << "\n--- foo(Tracer{\"temp\"}) ---\n";
	foo(Tracer{"temp"});
	std::cout << "\n--- m.show() ---\n";
	m.show();
	std::cout << "\n--- } ---\n";
}

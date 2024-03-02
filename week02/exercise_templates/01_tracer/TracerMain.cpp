#include "Tracer.hpp"
#include <numeric>
#include <ranges>
#include <vector>

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
		foo(std::move(inner));
		std::cout << "\n--- auto trace = bar(inner) ---\n";
		auto trace = bar(inner);
		std::cout << "\n--- trace.show() ---\n";
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

	std::vector<Tracer> v{};
	v.push_back(Tracer{"T1"});
	v.push_back(Tracer{"T2"});
	v.push_back(Tracer{"T3"});
	v.push_back(Tracer{"T4"});
	v.push_back(Tracer{"T5"});
	v.push_back(Tracer{"T6"});
	
	// std::vector<int> vint(1000000000);
	// std::iota(vint.begin(), vint.end(), 12);

	// auto start = std::chrono::system_clock::now();
	// std::vector<int> v_copy { vint };
	// std::chrono::duration<double> delta = std::chrono::system_clock::now() - start;
	// std::cout << "copying the container took: " << delta.count() << "s time\n";

	// auto start2 = std::chrono::system_clock::now();
	// std::vector<int> v_copy2 { std::move(vint) };
	// std::chrono::duration<double> delta2 = std::chrono::system_clock::now() - start2;
	// std::cout << "moving the container took : " << delta2.count() << "s time\n";

	std::cout << "---vector tracers---" << std::endl;
	std::ranges::for_each(v, [](Tracer & t) {
		t.show();
	});
	std::cout << "---end vector tracers---" << std::endl;

	std::cout << "\n--- creating sink and source ---\n";
	Tracer sink {"sink"}, source {"source"};

	std::cout << "\n--- assigning source to sink ---\n";
	sink = std::move(source);

	std::cout << "\n--- showing sink ---\n";
	sink.show();

	std::cout << "\n--- showing source ---\n";
	source.show();

	std::cout << "\n--- end of main ---\n";

}

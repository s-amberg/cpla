#include <asio.hpp>

#include <algorithm>
#include <thread>
#include <vector>

int parse(std::vector<char>) {
	return 42;
}

int main() {
	auto context = asio::io_context { };

	// start some async operations

	auto runners = std::vector<std::thread> { };

	for (int i { }; i < std::thread::hardware_concurrency(); ++i) {
		runners.push_back(std::thread { [&] {
			context.run();
		}});
    }

	for_each(runners.begin(), runners.end(), [](auto &runner) {
		runner.join();
	});
}

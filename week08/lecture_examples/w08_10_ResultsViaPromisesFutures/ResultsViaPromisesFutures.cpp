#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int main() {
	using namespace std::chrono_literals;

	auto promise = std::promise<int>{};
	auto result = promise.get_future();

	auto thread = std::thread { [&] {
		std::this_thread::sleep_for(2s);
		promise.set_value(42);
	}};

	std::this_thread::sleep_for(1s);

	std::cout << "The answer is: " << result.get() << '\n';

	thread.join();
}

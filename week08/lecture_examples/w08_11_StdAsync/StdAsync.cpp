#include <future>
#include <iostream>

int main() {
	auto the_answer = std::async([] {
		// Calculate for 7.5 million years
			return 42;
	});
	std::cout << "The answer is: " << the_answer.get() << '\n';
}

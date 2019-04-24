#include <algorithm>
#include <iostream>
#include <iterator>

#include <thread>

void doSomethingElse() {
	throw "surprise";
}

void longRunningAction() {
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(1s);
}

void calcAsync() {
  std::thread t{longRunningAction};
  doSomethingElse();
  t.join();
}

void countAs(std::string_view str) {
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(1s);
	auto nOfA = std::count(std::begin(str), std::end(str), 'A');
	std::cout << "A: " << nOfA;
}

void countAsync(std::string_view input) {
  std::thread t{[&] {
	 countAs(input);
  }};
  t.detach();
}


int main() {
	countAsync("AAA");
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(2s);
	//calcAsync();
}

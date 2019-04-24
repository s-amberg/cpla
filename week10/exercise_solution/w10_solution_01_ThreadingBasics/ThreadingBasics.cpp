#include <functional>

#include <iostream>

#include <thread>


struct IdPrinter {
	void operator()(std::ostream & out) const {
		out << std::this_thread::get_id() << '\n';
	}
};

void printId(std::ostream & out) {
	out << std::this_thread::get_id() << '\n';
}


int main() {
	auto idPrintLambda = [](std::ostream & out) {
		out << std::this_thread::get_id() << '\n';
	};
	std::thread tFunctor{IdPrinter{}, std::ref(std::cout)};
	std::thread tFunction{printId, std::ref(std::cout)};
	std::thread tLambda{idPrintLambda, std::ref(std::cout)};
	tLambda.join();
	tFunction.join();
	tFunctor.join();
}

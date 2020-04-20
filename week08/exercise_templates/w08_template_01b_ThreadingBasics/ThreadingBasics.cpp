#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

static bool isPrime(unsigned long long number) {
	for (auto factor = 2ull; factor * factor <= number; factor++) {
		if (number % factor == 0) {
			return false;
		}
	}
	return true;
}

static unsigned long long countPrimes(unsigned long long start, unsigned long long end) {
	unsigned long long count { };
	for (unsigned long long number = start; number < end; number++) {
		if (isPrime(number)) {
			count++;
		}
	}
	return count;
}

static unsigned long long countPrimesParallel(unsigned long long start, unsigned long long end, unsigned numberOfThreads) {
	unsigned long long range = (end - start) / numberOfThreads;
	std::vector<std::thread> threads { };
	std::vector<unsigned long long> results(numberOfThreads, 0);

	//TODO: Implement parallel solution

	return 0;
}


constexpr unsigned long long start = 1000000;
constexpr unsigned long long end = 10000000;
constexpr unsigned numberOfThreads = 1;

void measure() {
	auto const startTime = std::chrono::high_resolution_clock::now();

	auto const result = countPrimes(start, end);

	auto const endTime = std::chrono::high_resolution_clock::now();
	auto const duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	std::cout << "counted " << result << " primes in " << duration.count() << "ms" << std::endl;
}

int main() {
	measure();
}

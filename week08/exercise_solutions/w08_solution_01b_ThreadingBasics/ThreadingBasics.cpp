#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <utility>
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

	for (auto i = 0u; i < numberOfThreads; i++) {
		unsigned long long rangeStart = start + i * range;
		unsigned long long rangeEnd = rangeStart + range;
		std::cout << "Starting thread for range [" << rangeStart << ", " << rangeEnd << ']' << std::endl;
		std::thread thread { [=, &results] {
			results[i] = countPrimes(rangeStart, rangeEnd);
		} };
		threads.push_back(std::move(thread));
	}

	std::for_each(std::begin(threads), std::end(threads), [](auto & thread) {
		thread.join();
	});
	return std::accumulate(std::begin(results), std::end(results), 0ull);
}
constexpr unsigned long long start = 1000000;
constexpr unsigned long long end = 10000000;
constexpr unsigned numberOfThreads = 1;

void measure() {
	auto const startTime = std::chrono::high_resolution_clock::now();

	auto const result = countPrimesParallel(start, end, numberOfThreads);

	auto const endTime = std::chrono::high_resolution_clock::now();
	auto const duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	std::cout << "counted " << result << " primes in " << duration.count() << "ms" << std::endl;
}

int main() {
	measure();
}

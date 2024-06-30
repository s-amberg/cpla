#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <numeric>

struct Functor {
  auto operator()(std::ostream & out) -> void {
    out << std::this_thread::get_id();
  }
};

static void output(std::ostream & out) {
    out << std::this_thread::get_id();
}

static auto isPrime(unsigned long long number) -> bool {
  for (auto factor = 2ull; factor * factor <= number; factor++) {
    if (number % factor == 0) {
      return false;
    }
  }
  return true;
}

static auto countPrimes(unsigned long long start, unsigned long long end) -> unsigned long long {
  unsigned long long count{};
  for (unsigned long long number = start; number < end; number++) {
    if (isPrime(number)) {
      count++;
    }
  }
  return count;
}

static auto countPrimesParallel(unsigned long long start, unsigned long long end, unsigned numberOfThreads) -> unsigned long long {
  unsigned long long range = (end - start) / numberOfThreads;
  std::vector<std::thread> threads{};
  std::vector<unsigned long long> results(numberOfThreads, 0);

  for(unsigned t_id; t_id<numberOfThreads; t_id++) {
    threads.push_back(std::thread{[=,&results] {
      results.at(t_id) = countPrimes(start + t_id * range, std::min(start + (t_id + 1) * range, end));
    }});
  }

  std::for_each(std::begin(threads), std::end(threads), [](auto &thread) { thread.join(); });
  return std::accumulate(std::begin(results), std::end(results), 0ull);

}

constexpr unsigned long long start = 1000000;
constexpr unsigned long long end = 10000000;
constexpr unsigned numberOfThreads = 1;

auto measure() -> void {
  auto const startTime = std::chrono::high_resolution_clock::now();

  auto const result = countPrimes(start, end);

  auto const endTime = std::chrono::high_resolution_clock::now();
  auto const duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
  std::cout << "counted " << result << " primes in " << duration.count() << "ms" << std::endl;
}

auto main() -> int {
  // measure();
  std::thread thread1{Functor{}, std::ref(std::cout)};
  std::thread thread2{output, std::ref(std::cout)};
  std::thread thread3{[](std::ostream & out) {
    out << std::this_thread::get_id();
  }, std::ref(std::cout)};

  thread1.join();
  thread2.join();
  thread3.join();
}

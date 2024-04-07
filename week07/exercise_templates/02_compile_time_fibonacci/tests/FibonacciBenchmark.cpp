
#include "Fibonacci.hpp"
#include "catch2/catch_message.hpp"

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <sstream>
#include <utility>

//--------- 1d) Benchmark ---------

TEST_CASE("Fibonacci calculation", "[Fibonacci Benchmark Suite]") {
  // auto entry = GENERATE(table<unsigned long long, unsigned long long>({
  //   {0, 0}, 
  //   {1, 1}, 
  //   {2, 1}, 
  //   {3, 2}, 
  //   {4, 3}, 
  //   {5, 5}, 
  //   // {46, 1836311903} // Runs long!
  //   }));
  // auto input = std::get<0>(entry);
  // auto expected = std::get<0>(entry);
  // std::ostringstream oss;
  // oss << "Benchmark fibo(" << input << ")";
  // auto benchmarkName = oss.str();
  // BENCHMARK(std::move(benchmarkName)) {
  //   return fibo(input);
  // };
  // CAPTURE(input, expected);
  // REQUIRE(fibo(input) == expected);
}

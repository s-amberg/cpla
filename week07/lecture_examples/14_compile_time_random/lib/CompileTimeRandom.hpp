#ifndef COMPILE_TIME_RANDOM_HPP
#define COMPILE_TIME_RANDOM_HPP

#include <cstdint>

// Linear Congruential Generator

template <uint64_t m = 0xFFFFFFFFFFFFULL, uint64_t a = 0x5DEECE66DULL, uint64_t c = 0xBULL>
struct Rng {
  explicit constexpr Rng(unsigned seed = 1) : current{(seed ^ a) & m} {}

  constexpr auto next() -> int {
    current = (a * current + c) & m;
    return current >> 16;
  }

  constexpr auto nextBool() -> bool {
    return next() < 0;
  }

private:
  uint64_t current;
};

#endif
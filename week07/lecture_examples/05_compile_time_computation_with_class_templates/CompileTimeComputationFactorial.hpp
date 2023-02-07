#ifndef CTCFACTORIAL_HPP_
#define CTCFACTORIAL_HPP_

#include <cstddef>

template <std::size_t n>
struct fact {
  static std::size_t const value{(n > 1) ? n * fact<n - 1>::value : 1};
};

template <>
struct fact<0> {  // recursion base case: template specialization
  static std::size_t const value = 1;
};

#endif /* CTCFACTORIAL_HPP_ */

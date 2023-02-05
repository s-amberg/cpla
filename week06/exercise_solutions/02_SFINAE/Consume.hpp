#ifndef CONSUME_HPP
#define CONSUME_HPP

#include <concepts>
#include <type_traits>

enum class Result { Integer, Float, Other };

struct S1 {};
struct S2 {};
struct S3 {};


// #define TEMPLATE_PARAMETER_SFINAE
// #define RETURN_TYPE_SFINAE
// #define FUNCTION_PARAMETER_SFINAE
// #define CONCEPTS_SFINAE
#define CONCEPTS_TERSE

// Template Parameter SFINAE
#ifdef TEMPLATE_PARAMETER_SFINAE
template <
    typename T,
    typename = std::enable_if_t<std::negation_v<
        std::disjunction<std::is_integral<T>, std::is_floating_point<T>>>>>
auto consume(T value, S1 = {}) -> Result {
  return Result::Other;
}

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
auto consume(T value, S2 = {}) -> Result {
  return Result::Float;
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
auto consume(T value, S3 = {}) -> Result {
  return Result::Integer;
}


// Return Type SFINAE
#elif defined (RETURN_TYPE_SFINAE)
template <typename T>
auto consume(T value, S1 = {}) -> std::enable_if_t<
    std::negation_v<
        std::disjunction<std::is_integral<T>, std::is_floating_point<T>>>,
    Result> {
  return Result::Other;
}

template <typename T>
auto consume(T value, S2 = {})
    -> std::enable_if_t<std::is_floating_point_v<T>, Result> {
  return Result::Float;
}

template <typename T>
auto consume(T value, S3 = {})
    -> std::enable_if_t<std::is_integral_v<T>, Result> {
  return Result::Integer;
}


// Function Parameter SFINAE
#elif defined (FUNCTION_PARAMETER_SFINAE)
template <typename T>
auto consume(T value,
             std::enable_if_t<
                 std::negation_v<std::disjunction<std::is_integral<T>,
                                                  std::is_floating_point<T>>>,
                 S1> = {}) -> Result {
  return Result::Other;
}

template <typename T>
auto consume(T value, std::enable_if_t<std::is_floating_point_v<T>, S2> = {})
    -> Result {
  return Result::Float;
}

template <typename T>
auto consume(T value, std::enable_if_t<std::is_integral_v<T>, S3> = {})
    -> Result {
  return Result::Integer;
}


// Concepts SFINAE
#elif defined(CONCEPTS_SFINAE)

template <typename T>
auto consume(T value) -> Result {
  return Result::Other;
}

template <std::floating_point T>
auto consume(T value) -> Result {
  return Result::Float;
}

template <std::integral T>
auto consume(T value) -> Result {
  return Result::Integer;
}


// Concepts SFINAE with Terse Syntax
#elif defined(CONCEPTS_TERSE)

auto consume(auto value) -> Result {
  return Result::Other;
}

auto consume(std::floating_point auto value) -> Result {
  return Result::Float;
}

auto consume(std::integral auto value) -> Result {
  return Result::Integer;
}


#endif

#endif
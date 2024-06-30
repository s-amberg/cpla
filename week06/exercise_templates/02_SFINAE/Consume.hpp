#ifndef CONSUME_HPP
#define CONSUME_HPP
#include <concepts>
#include <type_traits>
enum class Result {
	Integer, Float, Other
};

struct Dummy1{};
struct Dummy2{};


template <typename T>
auto consume(T value) -> std::enable_if_t<std::negation_v<std::disjunction<std::is_integral<T>, std::is_floating_point<T>>>, Result> {
	return Result::Other;
}

template <typename T>
auto consume(T value, Dummy1 = {}) -> std::enable_if_t<std::is_integral_v<T>, Result> {
	return Result::Integer;
}

template <typename T>
auto consume(T value, Dummy2 = {}) -> std::enable_if_t<std::is_floating_point_v<T>, Result> {
	return Result::Float;
}


template<typename T>
concept is_int = std::is_integral<T>::value;

template<typename T>
concept is_float = std::is_floating_point<T>::value;

template <typename T>
auto consume_b(T value) -> Result{
	return Result::Other;
}
template <is_float T>
auto consume_b(T value) -> Result{
	return Result::Float;
}

template <is_int T>
auto consume_b(T value) -> Result{
	return Result::Integer;
}

auto consume_c(auto value) -> Result{
	return Result::Other;
}
auto consume_c(is_float auto value) -> Result{
	return Result::Float;
}
auto consume_c(is_int auto value) -> Result{
	return Result::Integer;
}


#endif
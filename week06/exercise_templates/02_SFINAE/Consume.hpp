#ifndef CONSUME_HPP
#define CONSUME_HPP

enum class Result {
	Integer, Float, Other
};


template <typename T>
auto consume(T value) -> Result {
	return Result::Other;
}


#endif
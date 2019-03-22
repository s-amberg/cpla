#ifndef LINEITERATOR_H_
#define LINEITERATOR_H_

#include <cstddef>
#include <iterator>
#include <string>

struct LineIterator {

	using iterator_category = std::input_iterator_tag;
	using value_type = std::string;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type *;
	using reference = value_type &;

	LineIterator() = default;
	explicit LineIterator(std::istream & in) : in { &in } {
	}

	bool operator==(LineIterator const & other) const {
		return is_not_good() && other.is_not_good();
	}

	bool operator!=(LineIterator const & other) const {
		return !(*this == other);
	}

	LineIterator & operator++() {
		std::getline(*in, current_line);
		return *this;
	}

	LineIterator operator++(int) {
		auto copy = *this;
		++*this;
		return copy;
	}

	value_type operator*() const {
		return current_line;
	}

private:
	std::istream * in{nullptr};
	value_type current_line{};

	bool is_not_good() const {
		return in == nullptr || (in->peek(), !in->good());
	}
};


#endif /* LINEITERATOR_H_ */

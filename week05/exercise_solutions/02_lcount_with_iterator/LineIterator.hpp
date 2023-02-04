#ifndef LINEITERATOR_HPP_
#define LINEITERATOR_HPP_

#include <cstddef>
#include <istream>
#include <iterator>
#include <string>

struct LineIterator {
  using iterator_category = std::input_iterator_tag;
  using value_type = std::string;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  LineIterator() = default;
  explicit LineIterator(std::istream& in) : in{&in} {}

  auto operator==(LineIterator const& other) const -> bool {
    return is_not_good() && other.is_not_good();
  }

  auto operator++() -> LineIterator& {
    std::getline(*in, current_line);
    return *this;
  }

  auto operator++(int) -> LineIterator {
    auto copy = *this;
    ++*this;
    return copy;
  }

  auto operator*() const -> value_type { return current_line; }

 private:
  std::istream* in{nullptr};
  value_type current_line{};

  [[nodiscard]] auto is_not_good() const -> bool {
    return in == nullptr || (in->peek(), !in->good());
  }
};

#endif /* LINEITERATOR_HPP_ */

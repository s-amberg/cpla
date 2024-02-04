#ifndef DYN_ARRAY_HPP
#define DYN_ARRAY_HPP

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <vector>

template <typename T>
struct DynArray {
  using container_type = std::vector<T>;
  using size_type = typename container_type::size_type;
  using index_type = std::ptrdiff_t;
  using reference = typename container_type::reference;
  using const_reference = typename container_type::const_reference;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;

  DynArray() = default;

  DynArray(std::initializer_list<T> items) : container{items} {}

  template <typename Iter>
  DynArray(Iter begin, Iter end) : container(begin, end) {}

  DynArray(size_type size, T value) : container(size, value) {}

  auto size() const -> size_type {
    return container.size();
  }

  auto empty() const -> bool {
    return container.empty();
  }

  auto at(index_type index) -> reference {
    return container.at(adapt_index(index));
  }

  auto at(index_type index) const -> const_reference {
    return container.at(adapt_index(index));
  }

  auto operator[](index_type index) -> reference {
    return at(index);
  }

  auto operator[](index_type index) const -> const_reference {
    return at(index);
  }

  auto resize(size_type new_size) -> void {
    container.resize(new_size);
  }

  auto push_back(T const &value) -> void {
    container.push_back(value);
  }

  auto pop_back() -> void {
    container.pop_back();
  }

  auto front() -> reference {
    return container.front();
  }

  auto front() const -> const_reference {
    return container.front();
  }

  auto back() -> reference {
    return container.back();
  }

  auto back() const -> const_reference {
    return container.back();
  }

  auto begin() -> iterator {
    return container.begin();
  }

  auto begin() const -> const_iterator {
    return container.begin();
  }

  auto cbegin() const -> const_iterator {
    return container.cbegin();
  }

  auto end() -> iterator {
    return container.end();
  }

  auto end() const -> const_iterator {
    return container.end();
  }

  auto cend() const -> const_iterator {
    return container.cend();
  }

  auto rbegin() -> reverse_iterator {
    return container.rbegin();
  }

  auto rbegin() const -> const_reverse_iterator {
    return container.rbegin();
  }

  auto crbegin() const -> const_reverse_iterator {
    return container.crbegin();
  }

  auto rend() -> reverse_iterator {
    return container.rend();
  }

  auto rend() const -> const_reverse_iterator {
    return container.rend();
  }

  auto crend() const -> const_reverse_iterator {
    return container.crend();
  }

private:
  container_type container{};

  auto adapt_index(index_type index) const -> size_type {
    if (index < 0) {
      return index + size();
    }
    return size_type(index);
  }
};

template <typename Iter>
DynArray(Iter, Iter) -> DynArray<typename std::iterator_traits<Iter>::value_type>;

#endif

#ifndef DYN_ARRAY_HPP
#define DYN_ARRAY_HPP

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <vector>
template <typename T>
struct DynArray {

    using container = std::vector<T>;
    using size_type = typename container::size_type;
    using index_type = std::ptrdiff_t;
    using reference = typename container::reference;
    using const_reference = typename container::const_reference;
    using iterator = typename container::iterator;
    using const_iterator = typename container::const_iterator;
    using reverse_iterator = typename container::reverse_iterator;
    using const_reverse_iterator = typename container::const_reverse_iterator;


    private:
    container content;



    public:

    DynArray() = default;
    DynArray(std::initializer_list<T> list) : content{list} {}
    DynArray(size_type count, T value) : content(count, value) {}

    template <typename Iter>
    DynArray(Iter begin, Iter end) : content(begin, end) {}

    auto makedynarray(std::initializer_list<T> list) -> DynArray<T> & {
        return DynArray(list);
    }

    auto size() const -> size_type {
        return content.size();
    }
    auto empty() const -> bool {
        return content.empty();
    }
    auto push_back(T const & value) -> void {
        return content.push_back(value);
    }
    auto pop_back() -> void {
        return content.pop_back();
    }
    auto front() -> reference {
        return content.front();
    }
    auto front() const -> const_reference {
        return content.front();
    }

    auto back() -> reference {
        return content.back();
    }
    auto back() const -> const_reference {
        return content.back();
    }

    auto at(index_type index) -> reference {
        size_type position = index >= 0 ? index : index + this->size();
        if(position > size()) throw std::invalid_argument("invalid index");
        return content.at(position);
    }
    auto at(index_type index) const -> const_reference {
        size_type position = index >= 0 ? index : index + this->size();
        if(position > size()) throw std::invalid_argument("invalid index");
        return content.at(position);
    }

    auto begin() -> typename container::iterator {
        return this->content.begin();
    }
    auto end() -> typename container::iterator {
        return this->content.end();
    }

    auto cbegin() -> typename container::const_iterator {
        return this->content.cbegin();
    }
    auto cend() -> typename container::const_iterator {
        return this->content.cend();
    }

    auto rbegin() -> typename container::reverse_iterator {
        return this->content.rbegin();
    }
    auto rend() -> typename container::reverse_iterator {
        return this->content.rend();
    }

    auto crbegin() -> typename container::const_reverse_iterator  {
        return this->content.crbegin();
    }
    auto crend() -> typename container::const_reverse_iterator  {
        return this->content.crend();
    }

    auto resize(size_type size) -> void {
        return content.resize(size);
    }


    auto operator[](index_type index) -> reference {
        return at(index);
    }

    auto operator[](index_type index) const -> const_reference {
        return at(index);
    }

};

template<typename Iter>
DynArray(Iter iter, Iter iterEnd) -> DynArray<typename std::iterator_traits<Iter>::value_type>;

#endif

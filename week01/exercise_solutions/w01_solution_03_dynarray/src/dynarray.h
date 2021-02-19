#ifndef DYNARRAY_H_
#define DYNARRAY_H_


#include <cstddef>
#include <initializer_list>
#include <vector>

template <typename T>
struct dynarray {
	using container_type = std::vector<T>;
	using size_type = typename container_type::size_type;
	using index_type = std::ptrdiff_t;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;
	using iterator = typename container_type::iterator;
	using const_iterator = typename container_type::const_iterator;
	using reverse_iterator = typename container_type::reverse_iterator;
	using const_reverse_iterator = typename container_type::const_reverse_iterator;

	dynarray() = default;
	dynarray(std::initializer_list<T> items) : container{items} {}
	template <typename Iter>
	dynarray(Iter begin, Iter end) : container(begin, end) {}
	dynarray(size_type size, T value) : container(size, value) {}

	size_type size() const {
		return container.size();
	}
	
	bool empty() const {
		return container.empty();
	}
	
	reference at(index_type index) {
		return container.at(adapt_index(index));
	}

	const_reference at(index_type index) const {
		return container.at(adapt_index(index));
	}

	reference operator[](index_type index) {
		return at(index);
	}

	const_reference operator[](index_type index) const {
		return at(index);
	}

	void resize(size_type new_size) {
		container.resize(new_size);
	}

	void push_back(T const & value) {
		container.push_back(value);
	}

	void pop_back() {
		container.pop_back();
	}

	reference front() {
		return container.front();
	}

	const_reference front() const {
		return container.front();
	}

	reference back() {
		return container.back();
	}

	const_reference back() const {
		return container.back();
	}

	iterator begin() {
		return container.begin();
	}

	const_iterator begin() const {
		return container.begin();
	}

	const_iterator cbegin() const {
		return container.begin();
	}

	iterator end() {
		return container.end();
	}

	const_iterator end() const {
		return container.end();
	}

	const_iterator cend() const {
		return container.cend();
	}

	reverse_iterator rbegin() {
		return container.rbegin();
	}

	const_reverse_iterator rbegin() const {
		return container.rbegin();
	}

	const_reverse_iterator crbegin() const {
		return container.crbegin();
	}

	reverse_iterator rend() {
		return container.rend();
	}

	const_reverse_iterator rend() const {
		return container.rend();
	}

	const_reverse_iterator crend() const {
		return container.crend();
	}

private:
	container_type container{};

	size_type adapt_index(index_type index) const {
		if (index < 0) {
			return index + size();
		}
		return size_type(index);
	}
};

template <typename T>
auto make_dynarray(std::initializer_list<T> items) -> dynarray<T> {
	return {items};
}

#endif /* DYNARRAY_H_ */

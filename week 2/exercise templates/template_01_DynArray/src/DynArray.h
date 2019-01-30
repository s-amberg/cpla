#ifndef DYNARRAY_H_
#define DYNARRAY_H_


#include <initializer_list>
#include <vector>

template<typename T>
class DynArray {
	using Container = std::vector<T>;
	Container values;

public:
	using size_type = typename Container::size_type;
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;
	using reverse_iterator = typename Container::reverse_iterator;
	using const_reverse_iterator = typename Container::const_reverse_iterator;

	DynArray() = default;

	DynArray(std::initializer_list<T> list) :
			values{list} {
	}

	template<typename ITER>
	DynArray(ITER b, ITER e) :
			values(b, e) {
	}

	DynArray(size_type n, T const & val) :
			values(n, val) {
	}
	size_type size() const {
		return values.size();
	}

	bool empty() const {
		return values.empty();
	}

	T & operator[](int index) {
		return at(index);
	}

	T const & operator[](int index) const {
		return at(index);
	}

	T & at(int index) {
		if (index < 0) {
			return values.at(size() + index);
		} else {
			return values.at(index);
		}
	}

	T const & at(int index) const {
		if (index < 0) {
			return values.at(size() + index);
		} else {
			return values.at(index);
		}
	}

	void push_back(T const & t) {
		values.push_back(t);
	}

	T const & front() const {
		return values.front();
	}

	T & front() {
		return values.front();
	}

	T const& back() const {
		return values.back();
	}

	T & back() {
		return values.back();
	}

	//TODO: Sol CPlA Ex02: Implementation of the pop_back() function returning std::optional<T>


	iterator begin() {
		return values.begin();
	}

	iterator end() {
		return values.end();
	}

	const_iterator begin() const {
		return values.begin();
	}

	const_iterator end() const {
		return values.end();
	}

	reverse_iterator rbegin() {
		return values.rbegin();
	}

	reverse_iterator rend() {
		return values.rend();
	}

	const_reverse_iterator rbegin() const {
		return values.rbegin();
	}

	const_reverse_iterator rend() const {
		return values.rend();
	}

	const_iterator cbegin() const {
		return values.cbegin();
	}

	const_iterator cend() const {
		return values.cend();
	}

	const_reverse_iterator crbegin() const {
		return values.crbegin();
	}

	const_reverse_iterator crend() const {
		return values.crend();
	}

	void resize(size_type newsize) {
		values.resize(newsize);
	}
};

template<typename T>
DynArray<T> make_dynArray(std::initializer_list<T> l) {
	return DynArray<T>(l);
}


#endif /* DYNARRAY_H_ */

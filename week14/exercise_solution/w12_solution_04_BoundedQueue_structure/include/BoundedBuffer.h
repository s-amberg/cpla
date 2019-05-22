#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_


#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename E>
struct BoundedBuffer {
	using value_type = E;
	using reference = value_type &;
	using const_reference = value_type const &;
	using size_type = size_t;

	explicit BoundedBuffer(size_type capacity) : bufferCapacity{capacity}, elements{std::make_unique<std::byte[]>(sizeof(E[capacity]))}{
		if (capacity == 0u) {
			throw std::invalid_argument{"A BoundedBuffer must not be empty!"};
		}
	}

	BoundedBuffer(BoundedBuffer const & other) : BoundedBuffer(other.bufferCapacity) {
		copyElements(other);
	}

	BoundedBuffer(BoundedBuffer && other) {
		swap(other);
	}

	~BoundedBuffer() {
		while (!empty()) {
			pop();
		}
	}

	BoundedBuffer & operator=(BoundedBuffer const & other) {
		if (this != &other) {
			BoundedBuffer cloneOther = other;
			swap(cloneOther);
		}
		return *this;
	}

	BoundedBuffer & operator=(BoundedBuffer && other) {
		if (this != &other) {
			swap(other);
		}
		return *this;
	}
	bool full() const {
		return numberOfElements == bufferCapacity;
	}

	bool empty() const {
		return numberOfElements == 0;
	}

	size_type size() const {
		return numberOfElements;
	}

	size_type capacity() const {
		return bufferCapacity;
	}

	void push(E const & element) {
		throwIfFull();
		new (&at(insertIndex()))value_type{element};
		//at(insertIndex()) = element;
		numberOfElements++;
	}

	void push(E && element) {
		throwIfFull();
		new (&at(insertIndex()))value_type{std::move(element)};
		//at(insertIndex()) = std::move(element);
		numberOfElements++;
	}

	void pop() {
		throwIfEmpty();
		front().~value_type();
		numberOfElements--;
		firstIndex = (firstIndex + 1) % bufferCapacity;
	}

	reference front() {
		throwIfEmpty();
		return at(firstIndex);
	}

	const_reference front() const {
		throwIfEmpty();
		return at(firstIndex);
	}

	reference back() {
		throwIfEmpty();
		return at(backIndex());
	}

	const_reference back() const {
		throwIfEmpty();
		return at(backIndex());
	}

	void swap(BoundedBuffer & other) {
		using std::swap;
		swap(bufferCapacity, other.bufferCapacity);
		swap(firstIndex, other.firstIndex);
		swap(numberOfElements, other.numberOfElements);
		swap(elements, other.elements);
	}
	
	template <typename...T>
	static BoundedBuffer make_buffer(T &&...element) {
		BoundedBuffer buffer{sizeof...(element)};
		buffer.push_many(std::forward<T>(element)...);
		return buffer;
	}

private:
	size_type bufferCapacity{};
	size_type firstIndex{};
	size_type numberOfElements{};
	std::unique_ptr<std::byte[]> elements;

	reference at(size_type index) {
		return *reinterpret_cast<value_type *>(&elements[index * sizeof(value_type)]);
	}

	const_reference at(size_type index) const {
		return *reinterpret_cast<value_type const *>(&elements[index * sizeof(value_type)]);
	}

	size_type insertIndex() const {
		return (firstIndex + numberOfElements) % bufferCapacity;
	}
	
	size_type backIndex() const {
		return (firstIndex + numberOfElements - 1) % bufferCapacity;
	}
	
	void throwIfEmpty() const {
		if (empty()) {
			throw std::logic_error{"Buffer is empty"};
		}
	}

	void throwIfFull() const {
		if (full()) {
			throw std::logic_error{"Buffer is full"};
		}
	}

	void copyElements(BoundedBuffer const & other) {
		for (auto index = 0u; index < other.size(); index++) {
			push(other.at(index));
		}
	}

	void push_many() {
	}

	template <typename First, typename...T>
	void push_many(First && first, T &&... elements) {
		push(std::forward<First>(first));
		push_many(std::forward<T>(elements)...);
	}
};


#endif /* BOUNDEDBUFFER_H_ */

#ifndef BOUNDEDQUEUE_H_
#define BOUNDEDQUEUE_H_

#include "BoundedBuffer.h"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <utility>

//TODO: Add template signature
struct BoundedQueue {

	//TODO: Add member types

	//TODO: Add constructors


	bool empty() const {
		//TODO: Implement
		return true;
	}

	bool full() const {
		//TODO: Implement
		return true;
	}

	size_type size() const {
		//TODO: Implement
		return 0;
	}

	void push(T const & element) {
		//TODO: Implement
	}

	void push(T && element) {
		//TODO: Implement
	}

	bool try_push(T const & element) {
		//TODO: Implement
		return false;
	}
	
	template <typename Rep, typename Period>
	bool try_push_for(T const & element, std::chrono::duration<Rep, Period> duration) {
		//TODO: Implement
		return false;
	}

	value_type pop() {
		//TODO: Implement
		return T{};
	}

	bool try_pop(T & ret) {
		//TODO: Implement
		return false;
	}

	template <typename Rep, typename Period>
	bool try_pop_for(T & ret, std::chrono::duration<Rep, Period> duration) {
		//TODO: Implement
		return false;
	}

	void swap(BoundedQueue & other) {
		//TODO: Implement
	}

private:
	BoundedBuffer<T> buffer;
	//TODO: Add mutex
};


#endif /* BOUNDEDQUEUE_H_ */

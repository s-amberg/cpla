#ifndef BOUNDEDQUEUE_H_
#define BOUNDEDQUEUE_H_

// #include "BoundedBuffer.hpp"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <utility>

//TODO: Add template signature
struct BoundedQueue {

	//TODO: Add member types

	//TODO: Add constructors
	template<typename U>
	BoundedQueue(U) {}


	auto empty() const -> bool {
		//TODO: Implement
		return true;
	}

	auto full() const -> bool {
		//TODO: Implement
		return true;
	}

	auto size() const -> size_type {
		//TODO: Implement
		return 0;
	}

	auto push(T const & element) -> void {
		//TODO: Implement
	}

	auto push(T && element) -> void  {
		//TODO: Implement
	}

	auto try_push(T const & element) -> bool {
		//TODO: Implement
		return false;
	}
	
	template <typename Rep, typename Period>
	auto try_push_for(T const & element, std::chrono::duration<Rep, Period> duration) -> bool {
		//TODO: Implement
		return false;
	}

	auto pop() -> value_type {
		//TODO: Implement
		return T{};
	}

	auto try_pop(T & ret) -> bool {
		//TODO: Implement
		return false;
	}

	template <typename Rep, typename Period>
	auto try_pop_for(T & ret, std::chrono::duration<Rep, Period> duration) -> bool {
		//TODO: Implement
		return false;
	}

	auto swap(BoundedQueue & other)  -> void {
		//TODO: Implement
	}

private:
	// BoundedBuffer<T> buffer;
	//TODO: Add mutex
};


#endif /* BOUNDEDQUEUE_H_ */

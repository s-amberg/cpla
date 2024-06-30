#ifndef BOUNDEDQUEUE_H_
#define BOUNDEDQUEUE_H_

#include "BoundedBuffer.hpp"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <utility>

template<typename T, typename Mutex = std::mutex, typename Condition = std::condition_variable>
struct BoundedQueue {

	using lock = std::unique_lock<Mutex>;
	using value_type = BoundedBuffer<T>::value_type;
	using reference = BoundedBuffer<T>::reference;
	using const_reference = BoundedBuffer<T>::const_reference;
	using size_type = BoundedBuffer<T>::size_type;

 	BoundedQueue() : BoundedQueue{10} { };
	BoundedQueue(size_type size) : buffer{BoundedBuffer<T>{size}} {
	};

	auto empty() const -> bool {
		lock lk{mx};
		return buffer.empty();
	}

	auto full() const -> bool {
		lock lk{mx};
		return buffer.full();
	}

	auto size() const -> size_type {
		return buffer.size();
	}

	auto push(T && element) -> void  {
		lock lk{mx};
		notFull.wait(lk, [this] {
			return !buffer.full();
		});
		buffer.push(std::move(element));
		notEmpty.notify_one();
	}

	auto push(T const & element) -> void  {
		lock lk{mx};
		notFull.wait(lk, [this] {
			return !buffer.full();
		});
		buffer.push(element);
		notEmpty.notify_one();
	}

	auto try_push(T const & element) -> bool {
		lock lk{mx};
		if(buffer.full()) return false;
		buffer.push(element);
		notEmpty.notify_one();
		return true;
	}
	
	template <typename Rep, typename Period>
	auto try_push_for(T const & element, std::chrono::duration<Rep, Period> duration) -> bool {
		lock lk{mx};
		notFull.wait_for(lk, duration, [this] {
			return !buffer.full();
		});
		if(!lk.owns_lock() || buffer.full()) return false;
		buffer.push(element);
		notEmpty.notify_one();
		return true;
	}

	auto pop() -> value_type {
		lock lk{mx};
		notEmpty.wait(lk, [this] {
			return !buffer.empty();
		});
		value_type popped =  std::move(buffer.front());
		buffer.pop();
		notFull.notify_one();
		return popped;
	}

	auto try_pop(T & ret) -> bool {
		lock lk{mx};
		if(buffer.empty()) return false;
		buffer.pop();
		notFull.notify_one();
		return true;
	}

	template <typename Rep, typename Period>
	auto try_pop_for(T & ret, std::chrono::duration<Rep, Period> duration) -> bool {
		lock lk{mx};
		notEmpty.wait_for(lk, duration, [this] {
			return !buffer.empty();
		});
		if(!lk.owns_lock() || buffer.empty()) return false;
		buffer.pop();
		notFull.notify_one();
		return true;
	}

	BoundedQueue(const BoundedQueue & other) : buffer{other.buffer} {
	}
	BoundedQueue(BoundedQueue && other) {
		this->swap(other);
	}

	auto swap(BoundedQueue & other) noexcept -> void {
		using std::swap;
		swap(buffer, other.buffer);
	}

	auto operator=(BoundedQueue const & other) -> BoundedQueue & {
		if(std::addressof(other) != this) {
			auto clone = BoundedQueue{other};
			swap(clone);
		}
		return *this;
	}
	auto operator=(BoundedQueue && other) -> BoundedQueue & {
		if(std::addressof(other) != this) {
			swap(other);
		}
		return *this;
	}    

private:
	BoundedBuffer<T> buffer;
	mutable Mutex mx{};
	Condition notEmpty{};
	Condition notFull{};
};


#endif /* BOUNDEDQUEUE_H_ */

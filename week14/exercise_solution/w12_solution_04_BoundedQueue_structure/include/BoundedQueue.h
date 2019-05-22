#ifndef BOUNDEDQUEUE_H_
#define BOUNDEDQUEUE_H_

#include "BoundedBuffer.h"

#include <chrono>

#include <condition_variable>
#include <mutex>
#include <utility>

template <typename T, typename Mutex = std::mutex, typename Condition = std::condition_variable>
struct BoundedQueue {

	using size_type = typename BoundedBuffer<T>::size_type;
	using value_type = typename BoundedBuffer<T>::value_type;
	using reference = typename BoundedBuffer<T>::reference;
	using const_reference = typename BoundedBuffer<T>::const_reference;

	using Guard = std::scoped_lock<Mutex>;
	using Lock = std::unique_lock<Mutex>;

	explicit BoundedQueue(size_type capacity) : buffer{capacity}{}

	BoundedQueue(BoundedQueue const & other) : buffer{other.cloneBuffer()} {
	}

	BoundedQueue(BoundedQueue && other) : BoundedQueue{1} {
		swap(other);
	}

	BoundedQueue & operator=(BoundedQueue const & other) {
		if (this != &other) {
			BoundedQueue copy{other};
			swap(copy);
		}
		return *this;
	}

	BoundedQueue & operator=(BoundedQueue && other) {
		if (this != &other) {
			swap(other);
		}
		return *this;
	}

	bool empty() const {
		Guard guard{mutex};
		return buffer.empty();
	}

	bool full() const {
		Guard guard{mutex};
		return buffer.full();
	}

	size_type size() const {
		Guard guard{mutex};
		return buffer.size();
	}

	void push(T const & element) {
		Lock lock{mutex};
		waitUntilNotFull(lock);
		buffer.push(element);
		notEmpty.notify_one();
	}

	void push(T && element) {
		Lock lock{mutex};
		waitUntilNotFull(lock);
		buffer.push(std::move(element));
		notEmpty.notify_one();
	}

	bool try_push(T const & element) {
		Lock lock{mutex};
		if (buffer.full()) {
			return false;
		}
		buffer.push(element);
		notEmpty.notify_one();
		return true;
	}
	
	template <typename Rep, typename Period>
	bool try_push_for(T const & element, std::chrono::duration<Rep, Period> duration) {
		Lock lock{mutex};
		if ( !notFull.wait_for(lock, duration, [this] {
			return !buffer.full();
		})) {
			return false;
		}
		buffer.push(element);
		notEmpty.notify_one();
		return true;
	}

	value_type pop() {
		Lock lock{mutex};
		notEmpty.wait(lock, [this] {
			return !buffer.empty();
		});
		T value = std::move(buffer.front());
		buffer.pop();
		notFull.notify_one();
		return value;
	}

	bool try_pop(T & ret) {
		Guard guard{mutex};
		if (buffer.empty()) {
			return false;
		}
		ret = std::move(buffer.front());
		buffer.pop();
		notFull.notify_one();
		return true;
	}

	template <typename Rep, typename Period>
	bool try_pop_for(T & ret, std::chrono::duration<Rep, Period> duration) {
		Lock lock{mutex};
		if (!notEmpty.wait_for(lock, duration, [this] {
			return !buffer.empty();
		})) {
			return false;
		}
		ret = std::move(buffer.front());
		buffer.pop();
		notFull.notify_one();
		return true;
	}

	void swap(BoundedQueue & other) {
		std::scoped_lock both{mutex, other.mutex};
		buffer.swap(other.buffer);
	}

private:
	void waitUntilNotFull(Lock & lock) {
		notFull.wait(lock, [this] {
			return !buffer.full();
		});
	}

	BoundedBuffer<T> cloneBuffer() const {
		Guard guard{mutex};
		return buffer;
	}

//	struct BoundCondition {
//		explicit BoundCondition(std::function<bool()> predicate)
//		 : predicate{std::forward<Predicate>(predicate)}{}
//		    void wait(std::unique_lock<Mutex> & lock) {
//		    	condition.wait(lock, predicate);
//		    }
//		    void notifyOne() {
//		    	condition.notify_one();
//		    }
//	private:
//		Predicate predicate;
//		Condition condition{};
//	};

	BoundedBuffer<T> buffer;
	mutable Mutex mutex{};
//	BoundCondition notEmpty{[this]{!buffer.empty();}};
//	BoundCondition notFull{[this]{!buffer.full();}};
	Condition notEmpty{};
	Condition notFull{};
};


#endif /* BOUNDEDQUEUE_H_ */

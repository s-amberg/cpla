#ifndef MAILBOX_H_
#define MAILBOX_H_

#include <deque>
#include <condition_variable>
#include <mutex>
#include <utility>

template <typename T>
struct Mailbox {

	template <typename E>
	void put(E && element) {
		std::scoped_lock<std::mutex> lock{mutex};
		mails.emplace_back(std::forward<E>(element));
		notEmpty.notify_all();
	}

	T get() {
		std::unique_lock<std::mutex> lock{mutex};
		notEmpty.wait(lock, []{return !mails.empty();});
		T nextMessage = std::move(mails.front());
		mails.pop_front();
		return nextMessage;
	}
private:
	std::deque<T> mails{};
	mutable std::mutex mutex{};
	mutable std::condition_variable notEmpty{};
};


#endif /* MAILBOX_H_ */

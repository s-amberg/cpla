#ifndef MAILBOX_H_
#define MAILBOX_H_

#include <deque>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <utility>

template <typename T>
struct Mailbox {
	template <typename E>
	void put(E && element) {
		std::scoped_lock lock{mutex};
		mails.emplace_back(std::forward<E>(element));
		notEmpty.notify_all();
	}

	T get() {
		std::unique_lock lock{mutex};
		notEmpty.wait(lock, [this]{return !mails.empty();});
		return next();
	}

	std::optional<T> tryGet() {
		std::scoped_lock lock{mutex};
		if (mails.empty()) {
			return std::nullopt;
		}
		return next();
	}
private:
	std::deque<T> mails{};
	mutable std::mutex mutex{};
	mutable std::condition_variable notEmpty{};

	T next() {
		T nextMessage = std::move(mails.front());
		mails.pop_front();
		return nextMessage;
	}
};


#endif /* MAILBOX_H_ */

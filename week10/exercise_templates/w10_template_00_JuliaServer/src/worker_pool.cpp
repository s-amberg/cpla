#include "worker_pool.h"

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <mutex>
#include <utility>
#include <functional>

worker_pool::worker_pool(std::size_t worker_count) {
	for(auto worker_index = std::size_t{}; worker_index < worker_count; ++worker_index) {
		m_workers.emplace_back(std::bind(&worker_pool::run_work, this));
	}
}

worker_pool::~worker_pool() {
	m_stop = true;
	m_work_available.notify_all();
	for_each(begin(m_workers), end(m_workers), [](auto & worker) {
		worker.join();
	});
}

void worker_pool::submit(work_type work) {
	auto const lock = std::lock_guard { m_work_lock };
	m_work.push(std::move(work));
	m_work_available.notify_one();
}

void worker_pool::run_work() {
	while (true) {
		auto work = [this] {
			auto lock = std::unique_lock {m_work_lock};
			m_work_available.wait(lock, [this] {
						return m_stop || m_work.size();
					});

			if (m_stop) {
				return work_type {};
			}

			auto task = std::move(m_work.front());
			m_work.pop();
			return task;
		}();

		if(work) {
			work();
		} else {
			return;
		}
	}
}

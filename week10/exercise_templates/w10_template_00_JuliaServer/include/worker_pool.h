#ifndef INCLUDE_WORKER_POOL_H_
#define INCLUDE_WORKER_POOL_H_

#include <queue>
#include <functional>
#include <cstddef>
#include <vector>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <mutex>

struct worker_pool {
	using work_type = std::function<void ()>;

	explicit worker_pool(std::size_t worker_count);

	~worker_pool();

	void submit(work_type work);

private:
	void run_work();

	std::queue<work_type> m_work { };
	std::vector<std::thread> m_workers { };
	std::condition_variable m_work_available { };
	std::mutex m_work_lock { };
	std::atomic_bool m_stop { };
};

#endif /* INCLUDE_WORKER_POOL_H_ */

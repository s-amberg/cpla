#ifndef INCLUDE_WORKER_POOL_H_
#define INCLUDE_WORKER_POOL_H_

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <mutex>
#include <queue>
#include <stop_token>
#include <thread>
#include <vector>

struct worker_pool {
  using work_type = std::function<void()>;

  explicit worker_pool(std::size_t worker_count);

  ~worker_pool();

  auto submit(work_type work) -> void;

private:
  auto run_work(std::stop_token &stop_token) -> void;

  std::queue<work_type> m_work{};
  std::vector<std::jthread> m_workers{};
  std::condition_variable m_work_available{};
  std::mutex m_work_lock{};
};

#endif /* INCLUDE_WORKER_POOL_H_ */

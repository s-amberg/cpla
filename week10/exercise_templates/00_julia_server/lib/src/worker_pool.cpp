#include "worker_pool.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <mutex>
#include <utility>

worker_pool::worker_pool(std::size_t worker_count) {
  for (auto worker_index = std::size_t{}; worker_index < worker_count; ++worker_index) {
    m_workers.emplace_back([this](auto stop_token) { run_work(stop_token); });
  }
}

worker_pool::~worker_pool() {
  for_each(begin(m_workers), end(m_workers), [](auto & worker) {
    worker.request_stop();
  });
  m_work_available.notify_all();
}

void worker_pool::submit(work_type work) {
  auto const lock = std::lock_guard{m_work_lock};
  m_work.push(std::move(work));
  m_work_available.notify_one();
}

void worker_pool::run_work(std::stop_token &stop_token) {
  while (!stop_token.stop_requested()) {
    auto work = work_type{};

    {
      auto lock = std::unique_lock{m_work_lock};
      m_work_available.wait(lock, [&] { return stop_token.stop_requested() || m_work.size(); });

      if (stop_token.stop_requested()) {
        return;
      }

      work = std::move(m_work.front());
      m_work.pop();
    }

    std::invoke(work);
  }
}

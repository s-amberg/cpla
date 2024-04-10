// #include "BoundedQueue.hpp"

#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <type_traits>
#include <utility>

struct single_threaded_test_mutex {
  static unsigned lock_count;
  static unsigned unlock_count;
  static unsigned try_lock_count;

  auto lock() -> void {
    lock_count++;
  }

  auto unlock() -> void {
    unlock_count++;
  }

  auto try_lock() -> bool {
    try_lock_count++;
    return true;
  }

  static auto reset_counters() -> void {
    lock_count = 0;
    unlock_count = 0;
    try_lock_count = 0;
  }
};

unsigned single_threaded_test_mutex::lock_count{0};
unsigned single_threaded_test_mutex::unlock_count{0};
unsigned single_threaded_test_mutex::try_lock_count{0};

template <std::size_t nOfFalseTries>
struct single_threaded_count_down_mutex : public single_threaded_test_mutex {
  std::size_t remaining_tries = nOfFalseTries;

  auto try_lock() -> bool {
    single_threaded_test_mutex::try_lock();
    if (remaining_tries == 0) {
      return true;
    }
    remaining_tries--;
    return false;
  }
};
namespace single_threaded_condition_variable_counters {
static std::size_t wait_count{0};
static std::size_t notify_count{0};
static std::size_t bad_waits{0};
static bool docheck{false};
static auto reset_counters() -> void {
  using namespace single_threaded_condition_variable_counters;
  wait_count = 0;
  notify_count = 0;
  bad_waits = 0;
  docheck = true;
}
} // namespace single_threaded_condition_variable_counters
template <std::size_t waitc = 0, std::size_t notifyc = 0, bool DO_CHECK = false>
struct single_threaded_condition_variable {
  single_threaded_condition_variable() {
    using namespace single_threaded_condition_variable_counters;
    docheck = DO_CHECK; // scharf stellen mit reset_counters()
  }
  ~single_threaded_condition_variable() noexcept(false) {
    using namespace single_threaded_condition_variable_counters;
    if (!docheck)
      return;
    try {
      REQUIRE(wait_count == waitc);
      REQUIRE(notify_count == notifyc);
      REQUIRE(bad_waits == 0);
    } catch (...) {
      docheck = false;
      throw;
    }
  }
  template <typename LOCK, typename COND>
  auto wait(LOCK &mx, COND cond) -> void {
    using namespace single_threaded_condition_variable_counters;
    static_assert(std::is_convertible<decltype(cond()), bool>::value, "condition must return bool");
    ++wait_count;
    inner_condition.wait(mx, cond);
    REQUIRE(cond());
  }
  template <typename LOCK>
  auto wait(LOCK &mx) -> void {
    using namespace single_threaded_condition_variable_counters;
    //		static_assert(false,"must not use wait without condition, bad practice");
    ++wait_count;
    inner_condition.wait(mx);
  }
  template <typename LOCK, typename COND, typename REP, typename PER>
  auto wait_for(LOCK &mx, std::chrono::duration<REP, PER> const &dur, COND cond) -> bool {
    using namespace single_threaded_condition_variable_counters;
    static_assert(std::is_convertible<decltype(cond()), bool>::value, "condition must return bool");
    ++wait_count;
    return inner_condition.wait_for(mx, dur, cond);
  }
  template <typename LOCK, typename REP, typename PER>
  auto wait_for(LOCK &mx, std::chrono::duration<REP, PER> const &dur) -> bool {
    using namespace single_threaded_condition_variable_counters;
    //		static_assert(false,"must not use wait without condition, bad practice");
    ++wait_count;
    return inner_condition.wait_for(mx, dur);
  }
  auto notify_all() -> void {
    using namespace single_threaded_condition_variable_counters;
    ++notify_count;
    inner_condition.notify_all();
  }
  auto notify_one() -> void {
    using namespace single_threaded_condition_variable_counters;
    ++notify_count;
    inner_condition.notify_one();
  }
  static auto check() -> bool {
    using namespace single_threaded_condition_variable_counters;
    return bad_waits == 0 && wait_count <= notify_count;
  }

private:
  std::condition_variable_any inner_condition{};
};

auto reset_counters() -> void {
  single_threaded_test_mutex::reset_counters();
  single_threaded_condition_variable_counters::reset_counters();
}

TEST_CASE("Push rvalue acquires lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue{5};
    // reset_counters();

    // queue.push(1);

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("Push rvalue releases lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue{5};
    // reset_counters();

    // queue.push(1);

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("Push lvalue acquires lock", "[Single Threaded Lock Suite]") {
    // int i{1};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue{5};
    // reset_counters();

    // queue.push(i);

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("Push lvalue releases lock", "[Single Threaded Lock Suite]") {
    // int i{1};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue{5};
    // reset_counters();

    // queue.push(i);

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("Pop acquires lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue{5};
    // queue.push(1);
    // reset_counters();

    // queue.pop();

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("Pop releases lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue{5};
    // queue.push(1);
    // reset_counters();

    // queue.pop();

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("Empty acquires lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue{5};
    // reset_counters();

    // queue.empty();

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("Empty releases lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue{5};
    // reset_counters();

    // queue.empty();

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("Full acquires lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue{5};
    // reset_counters();

    // queue.full();

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("Full releases lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue{5};
    // reset_counters();

    // queue.full();

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("Size acquires lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue{5};
    // reset_counters();

    // queue.size();

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("Size releases lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<>> queue{5};
    // reset_counters();

    // queue.size();

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("Swap acquires two locks", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<>> queue{5}, other{4};
    // reset_counters();

    // queue.swap(other);

    // REQUIRE(single_threaded_test_mutex::lock_count + single_threaded_test_mutex::try_lock_count == 2);
}

TEST_CASE("Swap releases two locks", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<>> queue{5}, other{4};
    // reset_counters();

    // queue.swap(other);

    // REQUIRE(single_threaded_test_mutex::unlock_count == 2);
}

TEST_CASE("Swap acquires tries multiple times to try_lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_count_down_mutex<3>, single_threaded_condition_variable<>> queue{5}, other{4};
    // reset_counters();

    // queue.swap(other);

    // REQUIRE(single_threaded_test_mutex::try_lock_count == 7);
}

TEST_CASE("Swap successful after delayed lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_count_down_mutex<1>, single_threaded_condition_variable<1, 1>> queue{5}, other{4};
    // other.push(17);
    // reset_counters();

    // queue.swap(other);

    // REQUIRE(queue.pop() == 17);
}

TEST_CASE("try_push rvalue acquires lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue{5};
    // reset_counters();

    // queue.try_push(1);

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("try_push rvalue releases lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue{5};
    // reset_counters();

    // queue.try_push(1);

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("try_push lvalue acquires lock", "[Single Threaded Lock Suite]") {
    // int i{1};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue{5};
    // reset_counters();

    // queue.try_push(i);

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("try_push lvalue releases lock", "[Single Threaded Lock Suite]") {
    // int i{1};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue{5};
    // reset_counters();

    // queue.try_push(i);

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("try_pop acquires lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue{5};
    // queue.push(1);
    // int result{};
    // reset_counters();

    // queue.try_pop(result);

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("try_pop releases lock", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue{5};
    // queue.push(1);
    // int result{};
    // reset_counters();

    // queue.try_pop(result);

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("No lock on size constructor", "[Single Threaded Lock Suite]") {
    // reset_counters();

    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> queue{5};

    // REQUIRE(single_threaded_test_mutex::lock_count == 0);
}

TEST_CASE("No unlock on size constructor", "[Single Threaded Lock Suite]") {
    // reset_counters();

    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> queue{5};

    // REQUIRE(single_threaded_test_mutex::unlock_count == 0);
}

auto same_locks_and_unlocks() -> bool {
  return single_threaded_test_mutex::unlock_count == single_threaded_test_mutex::lock_count + single_threaded_test_mutex::try_lock_count;
}

TEST_CASE("Symmetric lock and unlock on copy constructor", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> queue{5};
    // reset_counters();

    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> copy{queue};

    // REQUIRE(same_locks_and_unlocks());
}

TEST_CASE("Symmetric lock and unlock on move constructor", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> queue{5};
    // reset_counters();

    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> moved{std::move(queue)};

    // REQUIRE(same_locks_and_unlocks());
}

TEST_CASE("Symmetric lock and unlock on copy assignment", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue{5}, copy{4};
    // reset_counters();

    // copy = queue;

    // REQUIRE(same_locks_and_unlocks());
}

TEST_CASE("Symmetric lock and unlock on move assignment", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue{5}, moved{4};
    // reset_counters();

    // moved = std::move(queue);

    // REQUIRE(same_locks_and_unlocks());
}

TEST_CASE("try_push_for acquires lock on empty queue", "[Single Threaded Lock Suite]") {
    // int i{1};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue{5};
    // reset_counters();

    // queue.try_push_for(i, std::chrono::milliseconds{1});

    // REQUIRE(single_threaded_test_mutex::lock_count == 1);
}

TEST_CASE("try_push_for releases lock on empty queue", "[Single Threaded Lock Suite]") {
    // int i{1};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue{5};
    // reset_counters();

    // queue.try_push_for(i, std::chrono::milliseconds{1});

    // REQUIRE(single_threaded_test_mutex::unlock_count == 1);
}

TEST_CASE("try_pop_for aquires lock on empty queue", "[Single Threaded Lock Suite]") {
    // int result{};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue{5};
    // reset_counters();

    // queue.try_pop_for(result, std::chrono::milliseconds{1});

    // REQUIRE(single_threaded_test_mutex::lock_count == 2);
}

TEST_CASE("try_pop_for releases lock on empty queue", "[Single Threaded Lock Suite]") {
    // int result{};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue{5};
    // reset_counters();

    // queue.try_pop_for(result, std::chrono::milliseconds{1});

    // REQUIRE(single_threaded_test_mutex::unlock_count == 2);
}

TEST_CASE("try_push_for acquires lock on full queue", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue{1};
    // queue.push(1);
    // reset_counters();

    // queue.try_push_for(1, std::chrono::milliseconds{1});

    // REQUIRE(single_threaded_test_mutex::lock_count == 2);
}

TEST_CASE("try_push_for releases lock on full queue", "[Single Threaded Lock Suite]") {
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue{1};
    // queue.push(1);
    // reset_counters();

    // queue.try_push_for(1, std::chrono::milliseconds{1});

    // REQUIRE(single_threaded_test_mutex::unlock_count == 2);
}

TEST_CASE("try_pop_for acquires lock on full queue", "[Single Threaded Lock Suite]") {
    // int result{};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue{1};
    // queue.push(1);
    // reset_counters();

    // queue.try_push_for(result, std::chrono::milliseconds{1});

    // REQUIRE(single_threaded_test_mutex::lock_count == 2);
}

TEST_CASE("try_pop_for releases lock on full queue", "[Single Threaded Lock Suite]") {
    // int result{};
    // BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue{1};
    // queue.push(1);
    // reset_counters();

    // queue.try_push_for(result, std::chrono::milliseconds{1});

    // REQUIRE(single_threaded_test_mutex::unlock_count == 2);
}

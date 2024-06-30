#ifndef PETERSONMUTEXVOLATILE_H_
#define PETERSONMUTEXVOLATILE_H_

#include <atomic>

struct PetersonMutexVolatile {
  // acquire lock by thread 0
  auto thread0Lock() -> void {
    while(!state0.test_and_set());
    turn.store(1);
    while(state1.test() && turn.load() == 1);
  }

  auto thread0Unlock() -> void {
    state0.clear();
  }

  // acquire lock by thread 1
  auto thread1Lock() -> void {
    while(!state1.test_and_set());
    turn.store(0);
    while(state0.test() && turn.load() == 0);
  }

  // release lock by thread 1
  auto thread1Unlock() -> void {
    state1.clear();
  }

private:
  std::atomic_flag state0{false};
  std::atomic_flag state1{false};
  std::atomic<int> turn{0};
};

#endif /* PETERSONMUTEXVOLATILE_H_ */

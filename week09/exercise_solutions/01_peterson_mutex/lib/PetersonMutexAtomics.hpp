#ifndef PETERSONMUTEXATOMICS_H_
#define PETERSONMUTEXATOMICS_H_

#include <atomic>

struct PetersonMutexAtomics {
  // acquire lock by thread 0
  auto thread0Lock() -> void {
    state0 = true;
    turn = 1;
    while (turn == 1 && state1)
      ;
  }

  auto thread0Unlock() -> void {
    state0 = false;
  }

  // acquire lock by thread 1
  auto thread1Lock() -> void {
    state1 = true;
    turn = 0;
    while (turn == 0 && state0)
      ;
  }

  // release lock by thread 1
  auto thread1Unlock() -> void {
    state1 = false;
  }

private:
  std::atomic_bool state0{false};
  std::atomic_bool state1{false};
  std::atomic_int turn{0};
};

#endif /* PETERSONMUTEXATOMICS_H_ */

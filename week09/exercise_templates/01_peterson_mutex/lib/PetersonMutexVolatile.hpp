#ifndef PETERSONMUTEXVOLATILE_H_
#define PETERSONMUTEXVOLATILE_H_

struct PetersonMutexVolatile {
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
  volatile bool state0{false};
  volatile bool state1{false};
  volatile int turn{0};
};

#endif /* PETERSONMUTEXVOLATILE_H_ */

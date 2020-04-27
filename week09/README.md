# Exercise 9 - Memory Model and Atomics

In this exercise...

* ... apply atomics to the Peterson mutex in C++
* ... analyze code with data races and race conditions


# 0. IMPORTANT NOTE FOR TESTAT 3 `BoundedQueue` with Timed Operations

I (Felix) have forgotten to include the test suite for the third Testat in last weeks exercises.
The test suite is now in published in last weeks `exercise_templates` folder.
Please use the tests from this suites, in conjunction with you own tests, to test your Testat solution.

# 1. Peterson Mutex (Not Testat)
From the module Parallel Programming you should be familiar with the Peterson Mutex. If you need to recap it you can find it on the Skripte server [here](https://skripte.hsr.ch/Informatik/Fachbereich/Parallele_Programmierung/ParProg/Uebungen/09_Memory_Models_TESTAT2/).

Below you have the implementation ported to C++ using volatile. While this works in Java, it is incorrect in C++. 

```cpp
struct PetersonMutexVolatile {
    // acquire lock by thread 0
    void thread0Lock() {
        state0 = true;
        turn = 1;
        while (turn == 1 && state1);
    }

    void thread0Unlock() {
        state0 = false;
    }

    // acquire lock by thread 1
    void thread1Lock() {
        state1 = true;
        turn = 0;
        while (turn == 0 && state0);
    }

    // release lock by thread 1
    void thread1Unlock() {
        state1 = false;
    }
private:
    volatile bool state0 { false };
    volatile bool state1 { false };
    volatile int turn { 0 };
};
```

* It is necessary to use atomics to make the implementation work in C++. Create a type PetersonMutexAtomics that works correctly.
* You might need to set the build option in Cevelop to Release in order to enable optimizations. Otherwise, potentially incorrect implementations might not fail. 



# 2. Optional - CVU Student Critique (Not Testat)
In one of the past cvu magazines the following problem was posted:

Can you help the student and analyze her/his code and correct the bugs?

"I wanted to learn a bit about C++ threading to I tried writing a thread pool example. But it sometimes crashes - I've managed to get it down to a small example. Sometimes I get what I expected as output, for example: 
```
Worker done
Worker done
Ending thread #2
Ending thread #0
Worker done
Ending thread #1
Worker done
Ending thread #3
Worker done
All done
```

But other times I get a failure, for example:

```
Worker done
Ending thread #0
Worker done
Awaiting thread #1
Worker done
W
<crash>
```

I'm not sure what to do next - can you help? It is sufficient to recognize the issues, you don't need to solve them.

```cpp
#include <algorithm>
using namespace std;
#include <array>
#include <chrono>
using namespace chrono;
#include <cstdlib>
#include <iostream>
#include <thread>

static const int POOL_SIZE = 4;

// Allow up to 4 active threads
array<thread, POOL_SIZE> pool;

// Example 'worker' -- would in practice
// perform some, potentially slow, calculation
void worker()
{
  this_thread::sleep_for(
    milliseconds(rand() % 1000));


  cout << "Worker done\n";
}

// Launch the thread functoid 't' in a new
// thread, if there's room for one
template <typename T>
bool launch(T t)
{
  auto it = find_if(pool.begin(), pool.end(),
    [](thread const &thr)
    { return thr.get_id() == thread::id(); }
  );
  if (it == pool.end())
  {
    // everyone is busy
    return false;
  }
  *it = thread([=]()
  {
    t();
    thread self;
    swap(*it, self);
    self.detach();
    cout << "Ending thread #"
      << (it - pool.begin()) << "\n";
  });
  return true;
}

int main()
{
  while (launch(worker))
  {}

  // And run one in this thread
  // as an example of what we do
  // when the pool is full
  worker();

  for (auto & it : pool)
  {
    thread thread;
    swap(thread, it);
    if (thread.joinable())
    {
      cout << "Awaiting thread #"
        << (&it - &*pool.begin()) << "\n";
      thread.join();
    }
  }
  cout << "All done\n";
}
```

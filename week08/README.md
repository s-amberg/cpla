# Multi-Threading and Mutexes

In this exercise...

* ... you get familiar with the thread API of C++
* ... you will implement a thread-safe container

# 1. Basic Threading

***Note:*** On Linux you might need to add the `pthread` library to link the projects correctly: `Project Properties -> C++ General -> Paths & Symbols -> Libraries -> Add -> "pthread"`

## a) Thread IDs
Create a simple application that starts three threads:

* One thread shall be created with a functor
* One thread shall be created with a free function
* One thread shall be created with a lambda

Each thread prints its ID (`std::this_thread::get_id()`) on `std::cout`.

Since it is discouraged to use `std::cout` directly in your functor, function and lambda, each should have a `std::ostream & out` parameter. If you want to pass `std::cout` through the `std::thread` constructor, you have to wrap the argument in an `std::ref` on the call-site.

## b) Measure Speedup
In the template you have an implementation of a program that counts the prime numbers in a given range (`countPrimes` function). Parallelize the computation using multiple threads in `countPrimesParallel`.

***Note:*** Be aware, that each thread must only access his entry of the `results` array and that the `main`thread must only access those results after the threads have been joined.

What speedup can you achieve?

# 2. TESTAT 3: `BoundedQueue` with Timed Operations

In this exercise you will wrap your `BoundedBuffer` in a thread-safe `BoundedQueue`.

Please form groups of 3 students for testat hand-in:
* Submission in ALF if it is up and running (https://alf.sifs0005.infs.ch), otherwise, by email.
* Specify if you have worked in a group.
* Content: `BoundedQueue.h`
* You will get feedback as soon as possible
* Hand-in deadline: Thursday 9. May 2021 23:59

## a. Interface of `BoundedQueue`

Your `BoundedQueue` shall provide the following functionality:

* `push(T)` - Both copy and move / or forwarding. This operation blocks if the `BoundedQueue` is full.
* `T pop()` - Always returns the popped value. This operation blocks if the `BoundedQueue`is empty.
* `bool try_push(T const &)` - Tries to put a `T` into the queue. If the queue is not full and put operation has been successful it returns `true`, otherwise it returns `false`.
* `bool try_pop(T&)` - Tries to pop a `T` from the queue. If the queue is not empty and the pop operation has been suffessful it returns `true` and the popped value is in the out parameter, otherwise it returns `false`.
* `size()`, `empty()` and `full()`
* copy/move operations
* `bool try_push_for(T const &, std::chrono::duration)` - The same as `try_push`, but if the operation would block longer than the given duration it returns `false` too. The operation is not performed then.
* `bool try_pop_for(T &, std::chrono::duration)` - The same as `try_pop`, but if the operation would block longer than the given duration it returns `false` too. The operation is not performed then.

In order to avoid duplicating the whole implementation of `BoundedBuffer` you should write `BoundedQueue` as a wrapper for `BoundedBuffer` and delegate the functionality of the queue to it.

* Use strategized locking for your `BoundedQueue`. The used mutex and condition variable types shall be template parameters. Use `std::mutex` and `std::condition_variable` as default arguments.
* Make sure that exceptions do not keep the mutex locked. Use an appropriate standard wrapper type.

## b. Theory Questions

* Why does it not make sense to use `front()` and `back()` member functions for a thread-safe container?
* Why is it difficult to provide iterators for a thread-safe container?
* Why is `BoundedQueue::pop()` returning a `T` by value compared to the `void` return type of `BoundedBuffer::pop()`.

# Multi-Threading and Mutexes

In this exercise...

* ... you get familiar with the thread API of C++

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
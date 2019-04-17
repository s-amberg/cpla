# User Defined Literals

Goals:
In these exercises you will...

* ... implement your own user defined literal operators
* ... compare compile-time and run-time execution times
* ... apply tags and traits to implement conversions

## Compile-Time Fibonacci

1. Implement computing the `n`th fibonacci number in the following means as compile-time computation:

* a) With a constexpr function `fibo(unsigned)`
* b) With a variable template `fibo_v<unsigned>`
* c) With a user defined literal operator `5_fibo` that is evaluated at compile-time
* d)  Measure and compare the compilation and run-time for computing the 46th fibonacci number

2. Implement similar constructs to the above that return an `std::array<int, n>` filled with the `n` first fibonacci numbers instead.

* a) With a constexpr template function `fiboa` that takes the size of the array as template parameter. E.g. fiboa<5>()
* b) With a variable template `fiboa_v<int>`
* c) ***Optional (for experts):*** A user defined literal operator `10_fiboa` (returns an `array<int, 10>`). 


## Conversion with Tags and Traits

Implement a `temperature` literal type.
# Exercises Week 9 - User Defined Literals

Goals:
In these exercises you will...

* ... implement your own user defined literal operators
* ... compare compile-time and run-time execution times
* ... apply tags and traits to implement conversions

## 1. Compile-Time Fibonacci

1. Implement computing the `n`th fibonacci number in the following means as compile-time computation:

* a) With a constexpr function `fibo(unsigned)`
* b) With a variable template `fibo_v<unsigned>`. ***Hint:*** If you are using Cevelop, there might be an issue with parsing an expression containing varible templates. Therefore, you might want to put a reference to a varaible template in parentheses, to avoid ambiguities in the parse: `(fibo_v<n-2>)`.
* c) With a user defined literal operator `5_fibo` that is evaluated at compile-time
* d)  Measure and compare the compilation and run-time for computing the 46th fibonacci number. Does it make a difference regarding compilation time if the signature is changed to `fibo(unsigned const & n)`?

2. Implement similar constructs to the above that return an `std::array<int, n>` filled with the `n` first fibonacci numbers instead. Unfortunately, even though `std::array` is a literal type in C++17, its comparison operations are not `constexpr`. First implement a function for comparing the content of `std::array` at compile time: `arrayEquals`.  

* a) With a constexpr template function `fiboa` that takes the size of the array as template parameter. E.g. fiboa<5>()
* b) With a variable template `fiboa_v<int>`
* c) ***Optional (for experts):*** A user defined literal operator `10_fiboa` (returns an `array<int, 10>`). You will need to create infrastructure to parse the value of the literal.


## 2. Conversion with Tags and Traits

Implement a `temperature` literal type, similar to the `Speed` type you have seen in the lecture. The `Temperature` type shall be taggable with the units `Kelvin`, `Celcius` and `Fahrenheit`.

* Add the required tag types to the namespace `units::tags`.
* Specify the `Temperature` class template that stores the temperature in a `double` value.
* Implement comparison operations for the `Temperature` template for comparison with other objects of the same template instance (`==`, `!=`, `<`, `>`, `<=` and `>=`).
* Implement arithmetic operations for the `Temperature` template (`+`, `-`) - unary and binary.
* Implement the `ConversionTraits` class template with a `convert` member function and add a specialization for every possible conversion. You can lookup the conversion formula on the web.
* Implement a `temperatureCast` function template that delegates conversion to the `ConversionTraits` template.
* Add comparison operation templates to allow comparison of objects of arbitrary `Temperature` instances.
* Add user defined literal operators (`_K`, `_C`, `_F`) to the `unit::literals` namespace.

***Note:*** The project template for this exercies does not contain test cases for all operations above.
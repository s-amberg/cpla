# Exercise 10 - Threading and Asynchronous IO

In this exercise...

* ... you get familiar with the thread API of C++
* ... you implement basic asynchronous communication using ASIO
* ... you realize the communication logic in an existing application


# 1. Basic Threading

Create a simple application that starts three threads:

* One thread shall be created with a functor
* One thread shall be created with a free function
* One thread shall be created with a lambda

Each thread prints its ID (`std::this_thread::get_id()`) on `std::cout`.

Since it is discouraged to use `std::cout` directly in your functor, function and lambda, each should have a `std::ostream & out` parameter. If you want to pass `std::cout` through the `std::thread` constructor, you have to wrap the argument in an `std::ref` on the call-site.
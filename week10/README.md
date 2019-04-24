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

# 2. Standalone Asynchronous IO (Chat Client)

We have prepared projects using ASIO to implement a chat client-server application. It is the example ASIO chat client-server application from [here](https://think-async.com/Asio/asio-1.12.2/doc/asio/examples/cpp11_examples.html)

Preparation:
 * You need to download the ASIO library from [here](https://think-async.com/Asio/). You won't need to compile and install the library, but you need to add the include path of the extracted location to your project: `<asio-directory>/include`
 

***Note:*** If you are on Windows you need library dependencies that depend on the Windows platform!


# 3. Connect Four Game with SFML
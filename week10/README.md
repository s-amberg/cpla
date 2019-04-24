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
 

***Note:*** If you are on Windows you need library dependencies that depend on the Windows platform! The follwing libraries are required for this exercise: `ws2_32` and `wsock32`.

Get the project compiled. Besides the library dependencies you need to be aware, that there are two `main` functions in the project. We have created two build configurations: `Debug (Server)` and `Debug (Client)` which each have the other source file excluded.

It is easier to follow the message flow if you don't run all executables from the IDE. You can run them in separate terminal windows. The server will not feature any output at all. The client's messages will be distributed among all connected clients.

If you wan't the details about the source code, you can browse the API reference of [ASIO Documentation](https://think-async.com/asio/asio-1.12.2/doc/).


# 3. Connect Four Game with SFML
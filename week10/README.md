Exercise 10 - Network Programming
=================================

In this exercise you will ...

* ... implement a synchronous client for an HTTP webservice
* ... implement an asynchronous client for an HTTP webservice

# 0. Preparation

## B. General Setup

Since you will be needing a webservice to call from your solutions to this weeks exercises, we provide you with a basic http server that can render [Julia sets](https://en.wikipedia.org/wiki/Julia_set) as pretty images.
You will find the source code for the server application in the exercise templates under the name "00_julia_server".
Please make sure you can successfully build and run the application.
If you are having troubles with port 8080 already being in use on your machine, you can change the port the server is running on in the file "app/main.cpp".

When you have got the server up an running, you can test if it works by pointing your web browser at <http://127.0.0.1:8080> (adjust the port here if you had to change it in the server application).

***Important:*** If you are working in the devcontainer, you need to forward the port to your host system. To do this press `F1` open the ports view `Ports: Focus on Ports View` command and forward the configured port (i.e. `8080` by default)! 

If the server works correctly, you should be presented with the following Julia set:
![Default Julia set](julia.png)

The webservice provides you with a number of paramter to configure the Julia set, which you can specify as part of the query string.
Here is a list with all parameter names including their description, type and default values

* size -- The size of rendered image (Note: all images are rendered as squares) -- `Integer` -- 800
* exponent -- The exponent of the Julia function. Think of it as the degree of point-symetry -- `Integer` -- 2
* iterations -- The number of iteration to approximate the boundary condition -- `Integer` -- 100
* k_real -- The real part of the boundary condition. Think of it as turbulence -- `Floating-point` -- 0
* k_imaginary -- The imaginary part of the boundary condition. Think of it as turbulence -- `Floating-point` -- -1

For example, the following query will generate a Mandlebrot-esque Julia set with a 3-fold point symetry: <http://127.0.0.1:8080/?size=800&k_imaginary=0.75&k_real=0.03&exponent=3&iterations=128>

Please note that the rendering function currently operates in a single-threaded fashion.
Depending on the parameters you choose, the rendering process will take a varying amount of time.

## C. `simple_http` Quick Start

In order to simplify you life a little, we have implemented a small HTTP parser/generator library called `simple_http`.
Please note that this library is **not** production ready and only implements the subset of functionality required for these exercises.

In general, you will want to include the `simple_http.hpp` library header which will provide you with the required types and functions.
For you exercises, you will be working with the following types (member function lists are not necessarily complete but include what you will likely need):

```c++
namespace http {

  enum struct method {
    // ...
    get,
    // ...
  };

  enum struct header {
    // ...
    content_length,
    // ...
  };
  
  enum struct status_code {
    // ...
    ok,
    not_found,
    // ...    
  }

  struct request {
    // Construct a request with a given HTTP method
    explicit request(method m = method::get);
    
    // Set a parameter with the given name to a given value
    template<typename ValueType>
    auto parameter(std::string name, ValueType value) -> request &;
    
    // Write out the request to stream in a format suitable for transmission to an HTTP server
    friend auto operator<<(std::ostream & out, request const & req) -> std::ostream &;
  };

  struct response {
    // Construct a request with data on a stream
    explicit response(std::istream & in);
    
    // Extract the value of a given header field
    template<header HeaderField>
    auto get() const;
   
    // Retrieve the response body
    auto body() const -> std::string;
    
    // Set the body from data on a stream
    auto body(std::istream & in) -> response &;
    
    // Check whether the message is complete as if by `body().size == get<header::content_length>()`
    auto complete() const noexcept -> bool;
    
    // Retrieve the HTTP status code of the response
    auto status() const noexcept -> status_code;
  };

}

```

Of course you are encouraged to browse through the implementation of `simple_http`, but you are not required to do so.

# 1. Synchronous HTTP client

To get up to speed slowly, implement a synchronous client for the Julia webservice.
Use the `asio` types and functions you have seen in the lecture:

  * `asio::io_context`
  * `asio::ip::make_address(...)`
  * `asio::ip::tcp::endpoint`
  * `asio::ip::tcp::socket`
  * `asio::write(...)`
  * `asio::streambuf`
  * `asio::read_until(...)`
  * `asio::read(...)`
  * `asio::transfer_exactly(...)`

For a start, don't bother too much about error handling.
Request the default Julia set image from the webservice and save it with the filename `julia.bmp`

## Extension 1 (optional):

Implement some basic error handling.
You may choose from either passing an object of type `asio::error_code` to functions that might fail or using try/catch appropriately.

## Extension 2 (optional):

Read the parameters used to create the image from the standard input.
Use the appropriate function to modify you HTTP request.

# 2. Asynchronous HTTP client

With your synchronous client up and working, implement an asynchronous variant.
Use the respective `_async` variants of the blocking functions from from exercise 1.
Implement your solution in the `JuliaClient` class provided in the template (see the `TODO` notes in `JuliaClient.cpp`)

## Extension 1 (optional)

Make it possible for the user of your `JuliaClient` class to specify the output filename as well as the Julia set parameters.
Afterwards, use multiple `JuliaClient` objects to download multiple images at the same time, using different parameters and filenames.

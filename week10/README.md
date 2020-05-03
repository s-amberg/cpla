Exercise 10 - Network Programming
=================================

In this exercise you will ...

* ... implement a synchronous client for an HTTP webservice
* ... implement an asynchronous client for an HTTP webservice

# 0. Preparation

## A. Working With the Project Templates

While we generally don't force you to use any particular IDE, we strongly suggest you use Cevelop for this one.
The projects you will be working with depend on the "simple_http" library that can be found in the folder "exercise_libs".
We have implemented this Library in Cevelop and the exercise templates have all been configured to correctly reference this library.

## B. General Setup

Since you will be needing a webservice to call from your solutions to this weeks exercises, we provide you with a basic http server that can render [Julia sets](https://en.wikipedia.org/wiki/Julia_set) as pretty images.
You will find the source code for the server application in the exercise templates under the name "w10_template_00_JuliaServer".
Please make sure you can successfully build and run the application.
If you are having troubles with port 8080 already being in use on your machine, you can change the port the server is running on in the file "JuliaServer.cpp".

When you have got the server up an running, you can test if it works by pointing your web browser at <http://127.0.0.1:8080> (adjust the port here if you had to change it in the server application).
If the server works correctly, you should be presented with the following Julia set:
![Default Julia set](julia.bmp)

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

In general, you will want to include the `simple_http.h` library header which will provide you with the required types and functions.
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
    request & parameter(std::string name, ValueType value);
    
    // Write out the request to stream in a format suitable for transmission to an HTTP server
    friend std::ostream & operator<<(std::ostream & out, request const & req);
  };

  struct response {
    // Construct a request with data on a stream
    explicit response(std::istream & in);
    
    // Extract the value of a given header field
    template<header HeaderField>
    auto get() const;
   
    // Retrieve the response body
    std::string body() const;
    
    // Set the body from data on a stream
    std::string body(std::istream & in);
    
    // Check whether the message is complete as if by `body().size == get<header::content_length>()`
    bool complete() const noexcept;
    
    // Retrieve the HTTP status code of the response
    status_code status() const noexcept;
  };

}

```

Of course you are encouraged to browse through the implementation of `simple_http`, but it is not required that you do so.

# 1. Synchronous HTTP client

# 2. Asynchronous HTTP client

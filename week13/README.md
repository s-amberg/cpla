# Exercises 13 - Hourglass Interfaces

In this exercise you will apply the hourglass interface approach to a given library.

## 1. Fancy Lib

In the exercise directory you will find the following projects already prepared:

* Fancy (Shared Library) - Which contains the implementation of the `cppug::be_fancy` function. It is implemented in the `fancy_lib.hpp` and `fancy_lib.cpp` files.
```cpp
namespace cppug {
  void be_fancy(std::string const & ent, std::ostream & out) {
    out << "I am a fancy " << ent << '\n';
  }
}
```
* Doge (C++ Executable Application) - An executable project that accesses the `be_fancy` function through an overload version of `be_fancy`.
* Walrus (C Executable Application) - A C executable project that accesses the `be_fance` function through the C API `cppug_be_fancy_on_stdout(char const * const entitiy)`, which you will need to implement.
* Python (A Python Script) - `fancy_python.py` loads a shared library and calls the `cppug_be_fancy_on_stdout` function in the shared library, wrapped in its own `be_fancy` function.

### Your Task

* Implement the hourglass interface in the Fancy (Shared Library). 
  * Add a `fancy.h` header that offers the function `cppug_be_fancy_on_stdout(char const * const entitiy)`.
  * Implement the function in the `fancy.cpp` source file.
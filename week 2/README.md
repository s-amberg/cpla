# Exercises Week 2
Goals of this weeks exercises:
* You get familiar with language and library features new in C++17


## dynArray Extension ^

You have either already implemented the `dynArray` known from the C++ module previously, or you can take the template we have prepared for you [here](week 2/exercise templates/template_01_DynArray). You will add an extension to the `DynArray` container.

### `pop_back` with `std::optional<T>`

The `pop_back` call, which gets forwarded to `vector::pop_back` features undefined behavior in case of an empty container. And due to separation of *action* and *query* functions does not return the popped value. Change the implementation of the `DynArray::pop_back` member function to return a copy of the popped value wrapped in an `std::optional<T>`. If the container is empty, the `std::optional<T>` shall be empty too.


**Hint:** Write test cases first, for example:
``` cpp
DynArray<int> empty{};
std::optional<int> poppedValue = empty.pop_back():
ASSERT(!poppedValue);
```

### Class Template Deduction

Your test cases (probably), and the test cases of the solution of `DynArray` don't benefit from the template argument deduction for class templates yet. Go though the test cases and figure out in which declarations the explicit specification of the template arguments can already be omittet.



## Directory-Sizer 

Write a program using the filesystem library to compute the total size of all files in a given directory recursively. If no commmand line arguments are given take the current directory. If multiple command-line arguments are given sum up each individually and also present the total. Check if the information you can obtain from your OS corresponds with the output from your program.

call it like:
```
   $ mydirsize
```
or
```
   $ mydirsize /tmp
```
or
```
   $ mydirsize dirA dirB
```

How can you write test cases for your functionality? Note: you can employ the filesystem library also in your test cases!

**Hints:**
* On Windows: MinGW GCC 8.2 has a knwon bug in the `<filesystem>` header. It should be fixed with MinGW GCC 9.0. Instead you can use boost's filesystem library, which behaves identical in regard of this exercise.
..* Include: `<boost/filesystem.hpp>` - it is located in `<MinGW-Directory>/include`
..* Library: `boost_filesystem` - it is located in `<MinGW-Directory>/lib`

* For older compilers: Your compiler might not feature the filesystem library as expected by the C++17 standard. You might need to include `<experimental/filesystem>` instead of `<filesystem>` and use the namespace `std::experimental::filesystem` instead of `std::filesystem`.
    Add the `stdc++fs` library to your project (`Project Properties -> C/C++ General -> Paths and Symbols -> Library Tab`). 
    

## Fold Expressions

You already implemented the `readln` template function, which takes an `std::istream` and a variadic number of further arguments (by reference). It reads from the stream "into" each argument. The implementation required the specification of a variadic template and a base case (or a `sizeof...` check), for a call without arguments. The implementation could have looked as follows:

``` cpp
void doread(std::istream &) {
    return;
}

template<typename ...I>
void doread(std::istream &in, I&...vars);

template<typename FIRST, typename ...I>
void doread(std::istream &in, FIRST &var, I&...vars) {
    in >> var;
    doread(in, vars...);
}

```
    Take your solution of the `readln` exercise, or use the exercise project on github (Ex02_03_FoldRead) and simplify the `doread` function with a fold expression.
    Do you still need the base case? 

## if constexpr (Preview Exercise, Optional)

One new feature in C++17 we have not discussed in the lecture yet, are if constexpr statements. Using if `constexpr` provides the possibility to tell the compiler to conditionally enable code (at compile time), depending on some expression. This can be useful if you either have a system with distinct configurations for a target device, if your code depends on different versions of a library with more or less capabilities or to enable/disable certain sections in template code. It has already been possible to deal with such cases using the preprocessor or advanced template programming, but if `constexpr` features a much more readable way of achieving such things.

Let's have a look a a possible solution for the `increment` function from the previous week's exercises. We provide the code on _Compiler Explorer_: https://godbolt.org/g/JG5FKX

* Have a look at the code.
* If you change the type of the `value` variable from `int` to `unsigned` the overflow check is not required anymore. You should be able to observe that the corresponding section is not present in the compiled code in the function `increment_constexpr`. However, it is still present in the `increment` function.
* When you change the compiler from `clang` to `gcc`. You will observe that `gcc` also eliminates the overflow check for `increment` even though we have not enabled optimization. 
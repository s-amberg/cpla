# Exercises Week 2
Goals of this weeks exercises:
* You get familiar with language and library features new in C++17


## dynArray Extension ^

You have either already implemented the `dynArray` known from the C++ module previously, or you can take the solution of that exercise as a starting point for the tasks of the following exercises. You will add some extensions to the `dynArray` container.

1 https://github.com/PeterSommerlad/CPlusPlusLecture/tree/master/solws12/dynArray

**Important**: If you import the project, you need to adjust the compiler flag settings: Set the dialect to `-std=c++1z`! (`Project Properties -> C++ Build -> Settings -> GCC C++ Compiler -> Dialect.` Use the input field to enter the dialect, as C++17 is not available in the dropdown menu.

### `pop_back` with `std::optional<T>`

The `pop_back` call, which gets forwarded to `vector::pop_back` features undefined behavior in case of an empty container. And due to separation of action and query functions does not return the popped value. Change the implementation of the `dynArray::pop_back` member function to return a copy of the popped value wrapped in an `std::optional<T>`. If the container is empty, the `std::optional<T>` shall be empty too.


**Hint:** Write test cases first, for example:
``` cpp
dynArray<int> empty{};
std::optional<int> poppedValue = empty.pop_back():
ASSERT(!poppedValue);
```


### Class Template Deduction

Your test cases (probably), and the test cases of the solution of dynArray don't benefit from the template argument deduction for class templates yet. Go though the test cases and figure out in which declarations the explicit specification of the template arguments can already be omittet.


### Not an exercise for now

Later in the course, we will write deduction guides for the missing cases that still need the explicit specification of the template arguments.

**Experiment:** When the `dynArray` is initialized with string literals (`"Hello"`) the deduced type will be `char const *`. However, deducing the type `std::string` might be preferable. If you are very eager you can try to facilitate class templates and specializations thereof to replace `char const *` with `std::string` for this case. We will cover this topic later in the semester though.


## Directory-Sizer 

Write a program using the filesystem library to compute the total size of all files in a given directory recursively. If no commmand line arguments are given take the current directory. If multiple command-line arguments are given sum up each individually and also present the total. Check if the information you can obtain from your OS corresponds with the output from your program.

call it like:

   $ mydirsize

or

   $ mydirsize /tmp

or

   $ mydirsize dirA dirB

How can you write test cases for your functionality? Note: you can employ the filesystem library also in your test cases!

**Hints:*

    Your compiler might not feature the filesystem library as expected by the C++17 standard. You might need to include <experimental/filesystem> instead of <filesystem> and use the namespace std::experimental::filesystem instead of std::filesystem.
    Add the stdc++fs library to your linker options (Project Properties -> C/C++ Build -> Settings -> Linker -> Libraries). 
    
    Windows Issues with MinGW 8.2: Use boost
    

## Fold Expressions

You already implemented the readln template function, which takes an `std::istream` and a variadic number of further arguments (by reference). It reads from the stream "into" each argument. The implementation required the specification of a variadic template and a base case (or a `sizeof...` check), for a call without arguments. The implementation could have looked as follows:

``` cpp
void doread(std::istream &) {
    return;
}

template<typename ...I>
void doread(std::istream &in, I&...vars);

template<typename FIRST, typename ...I>
void doread(std::istream &in, FIRST &var, I&...vars) {
    in >> var;
    doread(in,vars...);
}

```
    Take your solution of the `readln` exercise, or use the exercise project on github (Ex02_03_FoldRead) and simplify the `doread` function with a fold expression.
    Do you still need the base case? 

## if constexpr (Preview Exercise, Optional)

One new feature in C++17 we have not discussed in the lecture yet, are if constexpr statements. Using if constexpr provides the possibility to tell the compiler to conditionally enable code (at compile time), depending on some expression. This can be useful if you either have a system with distinct configurations for a target device, if your code depends on different versions of a library with more or less capabilities or to enable/disable certain sections in template code. It has already been possible to deal with such cases using the preprocessor or advanced template programming, but if constexpr features a much more readable way of achieving such things.

Let's have a look a a possible solution for the increment function from the last exercises. We provide the code on _Compiler Explorer_: https://godbolt.org/g/JG5FKX

    Have a look at the code.
    If you change the type of the value variable from int to unsigned the overflow check is not required anymore. You should be able to observe that the corresponding section is not present in the compiled code anymore in the function increment_constexpr. However, it is still present in the increment function.
    When you change the compiler from clang to gcc. You will observe that gcc also eliminates the overflow check for increment even though we have not enabled optimization. 
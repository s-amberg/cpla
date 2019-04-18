# Exercises Week 3

Goals of this weeks exercises:

-   You experiment and observe the behavior of moved objects
    -   See the behavior of objects when used as lvalue and rvalue
    -   Observing copying and moving operations
    -   Understand when elements living in a `std::vector` are copied
        and moved


# 1. Tracing Calls

From CPlusPlus you might already be familiar with the tracer class as
used in the extra exercises.

**Important:** Since the released versions of GCC (7.2.0) and Clang
(5.0.0) seem to be actually creating a function for deduction guides,
you should refrain from relying on class template argument deduction for
this exercise! Otherwise, you might observe additional copies, which are
not neccessary. For this exercise: Prefer `std::vector<Tracer>` over
`std::vector`.

We have prepared an exercise project for you. It contains the `Tracer`
class and code it is used in. You find the exercise
[here](/../tree/master/week03/exercise_templates/w03_template_01_Tracer).

## Output of Tracer

Look at the code of the Tracer program and figure out what output it
generates and why. You can augment the `main()` function with additional
output to get a better overview of the statements' effects.

## Tracer in Standard Container

Observe the behavior of the Tracer type when used in an `std::vector`.

-   First, create an `std::vector<Tracer>`.
-   Second, add a `Tracer` object to the vector.
-   Keep adding further Tracers to the vector.
-   What happens to the elements of the vector?
-   How many times is `T1` copied?

    ``` cpp
    std::vector<Tracer> v{};
    v.push_back(Tracer{"T1"});
    v.push_back(Tracer{"T2"});
    v.push_back(Tracer{"T3"});
    v.push_back(Tracer{"T4"});
    ```

-   Make a copy of your vector. What happens?

    ``` cpp
    std::vector<Tracer> v_copy{v};
    ```

## Copy Assignment

Your Tracer type does not provide an assignment operator. Add one which
adds `" copy-assigned"` to the name and prints a notification about the
copy operation on `std::cout`, similar to the implemented constructors.

-   You can use the code below to invoke your assignment operator. It's
    just part of the `main` function.
-   Does the code below compile if you don't specify the copy-assignment
    operator?
-   Do you define the assignment operator as free or as member function?
    Why?

<!-- -->

``` cpp
int main() {
  //...
  std::cout << "\n--- creating sink and source ---\n";
  Tracer sink {"sink"}, source {"source"};

  std::cout << "\n--- assigning source to sink ---\n";
  sink = source;

  std::cout << "\n--- showing sink ---\n";
  sink.show();

  std::cout << "\n--- showing source ---\n";
  source.show();

  std::cout << "\n--- end of main ---\n";
}
```

## Move Construction/Assignment

Replace the copy constructor and copy-assignment operator of the tracer
class with a move constructor and a move-assignment operator:

-   In the move constructor set the name of the constructed Tracer to
    the name of the moved from Tracer and add `" moved"`. Change the
    parameter object's name to name plus `" moved away"`. Example:

    ``` cpp
    Tracer origin{"origin"};
    Tracer target{std::move(origin)};
    ```

Afterwards, target shall contain the name `"orgin moved"` and origin
shall contain the name `"origin moved away"`.

In the move assignment operator set the name of the name of the moved-to
object to the name of the moved from object and add `" move-assigned"`.
The moved from object shall have the moved to object's name plus
`" moved to"`. Example:

``` cpp
Tracer origin{"origin"};
Tracer target{"target"};
target = std::move(origin);
```

Afterwards, target shall contain the name `"origin move-assigned"` and
origin shall contain the name `"target moved to"`.

**Hint:** To avoid creating a temporary name in the move assignment
operator, use `std::swap` to exchange the names of the objects first:
`std::swap(name, other.name);`.

-   How does the behavior of the output change with respect to the
    implmentation with the copying tracer?
    -   You might need to wrap the local variable passed to function foo
        and the assignment with std::move to have the program compile
        with the move-only class Tracer.
    -   Explain why std::move is required. What would happen otherwise
        (without std::move)? Why does it not compile?
-   Does the bevhavior change when you disable copy-elision? GCC
    provides such an option (`-fno-elide-constructors`). Add it as a
    `Miscellaneous` flag for the project
    (`Properties -> C/C++ Build -> Settings -> Tool Settings -> GCC C++ Compiler -> Miscellaneous -> Other flags`)

What about the state of source after the move assignment?

-   We just know this shall have a valid state, but we don't know which
    state exactly. And it still must be destructed. Is this observable?
-   As you have a moveable type what happens if you just call
    `std::move` on a tracer object?
-   What is the output of the call below? Why?

    ``` cpp
    int main() {
      ...
      std::cout << "\n--- std::move(m) ---\n";
      std::move(m);
      std::cout << "\n--- end of main ---\n";
    }
    ```

## Vector Again

Now as your Tracer is movable:

-   Did the behavior in your vectors from the exercise above change?
-   Are the tracers always treated as you expected?
    -   If not, try to figure out why.
    -   It's a really advanced problem. Discuss it with your colleagues.

## Moving vs. Copying Large Objects

Large objects can benefit from move operations. An `std::vector`, for
example, allocates memory on the heap for storing its values. Copying a
vector requires additional heap space and copies all values to this new
memory location. Moving a vector just needs to move the pointers, which
access this memory, to the move-constructed/assigned vector.

Try to measure the difference in allocating, copying and moving a large
`std::vector`.

You can use std::chrono to measure the operations.

``` cpp
auto start = std::chrono::system_clock::now();
//allocate large vector
std::chrono::duration<double> delta = std::chrono::system_clock::now() - start;
std::cout << "creating the container took: " << delta.count() << "s time\n";
```

-   What size of vector is large enough to observe the behavior?

---
keywords:
- c++
title: 'Rvalue References / Move Semantics'
---


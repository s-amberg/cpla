# Exercises Week 2

Goals of this weeks exercises:

-   You experiment and observe the behavior of moved objects
    -   See the behavior of objects when used as lvalue and rvalue
    -   Observing copying and moving operations
    -   Understand when elements living in a `std::vector` are copied
        and moved
    -   Start with the first testat exercise


# 1. Tracing Calls

We have prepared an exercise project for you. It contains the `Tracer`
class and code it is used in. You find the exercise
[here](./exercise_templates/w02_template_01_Tracer).

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
    implementation with the copying tracer?
    -   You might need to wrap the local variable passed to function foo
        and the assignment with std::move to have the program compile
        with the move-only class Tracer.
    -   Explain why std::move is required. What would happen otherwise
        (without std::move)? Why does it not compile?
-   Does the behavior change when you disable copy-elision? GCC
    provides such an option (`-fno-elide-constructors`). Add it as a
    `Miscellaneous` flag for the project
    (`Properties -> C/C++ Build -> Settings -> Tool Settings -> GCC C++ Compiler -> Miscellaneous -> Other flags`)

What about the state of source after the move assignment?

-   We just know this shall have a valid state, but we don't know which
    state exactly. And it still must be destructed. Is this observable?
-   As you have a movable type what happens if you just call
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

You can use `std::chrono` to measure the operations.

``` cpp
auto start = std::chrono::system_clock::now();
//allocate large vector
std::chrono::duration<double> delta = std::chrono::system_clock::now() - start;
std::cout << "creating the container took: " << delta.count() << "s time\n";
```

-   What size of vector is large enough to observe the behavior?



# 2. `BoundedBuffer`

In this exercise you will create the fundamental data structure for a `BoundedBuffer`. This will be an ongoing task during. You will add and change features step-by-step during the semester. After certain milestones you will hand your result in as testat exercises to be reviewed by the exercise supervisor.

Please form groups of 2-3 students for testat hand-in:

* Send an email to [Thomas Corbat](mailto:thomas.corbat@ost.ch)
* ***Subject***: `[CPlA-Testat-1] name1 name2 name3`
* Content: `BoundedBuffer.h`
* You will get feedback as soon as possible
* Hand-in deadline: Monday 14. March 23:59 (MEZ)


A project template with predefined tests is available [here](./exercise_templates/w02_template_02_BoundedBuffer).

## Introduction

`BoundedBuffers` are used in environments that have one or many producers and an consumers. The `BoundedBuffer` is used as a shared data structure for passing elements from the producer to the consumer. A `BoundedBuffer` has a fixed capacity and therefore, features an upper limit of maximum number of elements it can contain. Usually, it is implemented as a *FIFO* queue. Consumers must not be able to retrieve data from an empty buffer and likewise a producer on the other hand, must not be able to write data into a full buffer.

Your implementation will use an [`std::array`](http://en.cppreference.com/w/cpp/container/array) as base data structure and will behave like a circular buffer.

Your `BoundedBuffer` features the following API:

* `empty` – queries whether the buffer is empty
* `full` – queries whether the buffer is full
* `size` – queries the number of elements currently in the buffer
* `front` – returns the first element in the buffer; it allows modification of the first element
* `back` – returns the last element in the buffer; it allows modification of the last element
* `push` – inserts a new element into the buffer
* `pop` – removes the first element from the buffer
* `swap` – swaps the contents with another `BoundedBuffer` (parameter)


Furthermore, your `BoundedBuffer` must feature the following *member types*:

* `value_type`
* `container_type`
* `reference`
* `const_reference`
* `size_type`

You get test suites for each task. Our recommendation is adding one test at a time. You can start by out-commenting every test. Adding one test will usually result in a red bar. Write just as much code to get the required functionality done (compiles and results in a green bar). Then start over with the next test case.

## Member Function Definitions (Signatures)

First implement the declarations of `BoundedBuffer`s members, without any logic, to get it compiled.

* ***Test-Suite***: `bounded_buffer_signatures_suite`

***Hint:*** If you are unsure about the signatures of the individual member functions you can get inspiration from the standard library. The [`std::queue`](http://en.cppreference.com/w/cpp/container/queue) offers a similar interface to your `BoundedBuffer`.

***Note:*** Some of the tests we provide are not really sensible for a real test scenario. But they will help you to get the signatures of your member functions right. There is a dependency to ***Boost*** (`type_index.h`). Accordingly, you need to have the [Boost library](http://www.boost.org) installed on your system and reference it from your project.

***Attention:*** The `boost` headers offered by the *CUTE* project wizard won't be sufficient, as they have an obsolete version.


## Behavior of a default-constructed `BoundedBuffer`

* Now implement the behavior of the member functions for a default-constructed `BoundedBuffer`. As always avoid *Undefined Behavior*.
* `empty` - returns `true`
* `full` – returns `false`, unless the buffer has been created with capacity `0`
* `size` – returns `0`
* `front` – throws an exception (`std::logic_error`)
* `back` – throws an exception (`std::logic_error`)
* `push` – inserts an element. However, you cannot observe this currently and you can ignore actually putting the element into a data structure for storage. If the `BoundedBuffer` has size `0` and exception (`std::logic_error`) will be thrown, because the buffer is `full()`.
* `pop` – throws an exception (`std::logic_error`)throws an exception (`std::logic_error`)
* `swap` – Nothing happens for empty buffer

* ***Test-Suite:*** `bounded_buffer_default_behavior_suite`


## Contents of a `BoundedBuffer`

Since you now have the buffer's interface implemented, you can start implementing the required logic. You have two possible approaches to implement an array-based circular buffer. You should already be familiar with that from the *Algorithmen & Datanstrukturen* lecture. Nevertheless, we will summarize the possibilities here:

* You store the index of the first element and you also store the number of elements currently in the buffer. This allows using an array of the actual buffer capacity.
* Alternatively, you work with some kind of pointers, in this case the array indices, to mark the start and end positions. The start position points to the first element and the end position points beyond the last element. In case start and end positions point to the same location the buffer is empty. This effectively reduces the number of possible elements in the buffer by one, because a full buffer would have the same state regarding start and end pointer. This would leave the two states indistinguishable only by the indices. Therefore, additional information would be required like a flag indication whether the buffer is empty or the fundamental array would need to have larger capacity, (`+1`) than the buffers capacity. 

The first approach is simpler to implement and easier to read. If you decide to implement the second approach you need to adapt the test checking the `BoundedBuffer::container` type.

Beside the general approach the behavior of the `BoundedBuffer` should be self-explanatory:

* As long as the buffer is not full you can push new elements into the buffer, otherwise an exception will be thrown
* As long as the buffer is not empty you can remove elements from the buffer, otherwise an exception will be thrown
* The basic principle of the `BoundedBuffer` is a *FIFO* queue. The element that is inserted first (`push()`) is removed first (`pop()`). The element first inserted can be accessed with `front()`. `back()` access the last inserted element.
* It is possible to exchange the content of two `BoundedBuffer`s using `swap(BoundedBuffer)`
* Prefer using the `array::at()` member function to recognize accidental out of bounds element access.

* Test suite: `bounded_buffer_content_suite`

Furthermore, there is an additional test suite that ensures the correct use of move and copy operations on the elements. This suite works with an mocked element type that tracks its memory operations and asserts the correct use counts afterwards. Be cautious to apply the correct move and copy operations!

* TestSuite: `bounded_buffer_semantic_suite`


## Constructors

So far the implicitly available constructors have been sufficient. Now explicitly implement them yourself. You need to make sure they use the suitable move or copy operations on the elements. The behavior and the tests of your `BoundedBuffer` will not change if you do it correctly. Implement the following special member functions:

* Default constructor
* Copy constructor
* Move constructor
* Copy assignment operator
* Move assignment operator

***Note:*** Currently, this task seems rather pointless. Later we will modify the `BoundedBuffer` to facilitate heap memory, this will require the implementation of our own constructors and assignment operators. It will be easier if you already have the correct structure as a starting point then.



---
keywords:
- c++
title: 'Rvalue References / Move Semantics'
- testat-1
---


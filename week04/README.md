# `BoundedBuffer`

In this exercise you will create the fundamental data structure for a `BoundedBuffer`. This will be an ongoing task during. You will add and change features step-by-step during the semester. After certain milestones you will hand your result in as testat exercises to be reviewed by the exercise supervisor.

Please form groups of 2-4 students for testat hand-in:
* Send an email to [Thomas Corbat](mailto:thomas.corbat@hsr.ch)
* ***Subject***: `[CPlA-Testat-1] hsrname1 hsrname2 hsrname3 hsrname4`
* Content: `BoundedBuffer.h`
* You will get feedback as soon as possible
* Hand-in deadline: Sunday 24. March 23:59 (MEZ)

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
* `push` – inserts an element. However, you cannot observe this currently and you can ignore actually putting the element into a data strcture for storage. If the `BoundedBuffer` has size `0` and exception (`std::logic_error`) will be thrown, because the buffer is `full()`.
* `pop` – throws an exception (`std::logic_error`)throws an exception (`std::logic_error`)
* `swap` – Nothing happens for empty buffer

* ***Test-Suite:*** `bounded_buffer_default_behavior_suite`


## Contents of a `BoundedBuffer`

Since you now have the buffer's interface implemented, you can start implementing the required logic. You have two possible approaches to implement an array-based circular buffer. You should already be familiar with that from the *Algorithmen & Datanstrukturen* lecture. Nevertheless, we will summarize the possibilities here:
* Either you work with some kind of pointers, in this case the array indices, to mark the start and end positions. The start position points to the first element and the end position points beyond the last element. In case start and end positions point to the same location the buffer is empty. This effectively reduces the number of possible elements in the buffer by one, because a full buffer would have the same state regarding start and end pointer. This would leave the two states indistinguishable only by the indicies. Therefore, additional information would be required like a flag indication whether the buffer is empty or the fundamental array would need to have larger capacity, (`+1`) than the buffers capacity. 
* Alternatively, you only store the index of the first element, similar to the start position above. But instead of also storing the end position, you just store the number of elements currently in the buffer. This allows using an array of the actual buffer capacity.

The latter approach is simpler to implement and easier to read. If you decide to implement the first approach you need to adapt the test checking the `BoundedBuffer::container` type.

Beside the general approach the behvior of the `BoundedBuffer` should be self-explanatory:
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



# Type Deduction Trivia

In the lecture you have been taught about type deduction for function templates (and `auto`), e.g. in source code as follows:

```cpp
template<typename T>
void f(T && t) {...}
```

When the template above is instantiated, the type `T` is deduced, which also implies the specific type of the parameter `t`. This deduction follows specific rules, depending on the declared template parameter type (above `T&&`). If you don't recall them exactly, have a look at the corresponding slides. If you have trouble understanding the rules, discuss them with your colleagues or ask your supervisor.

Once you are confident, you can play a game we have prepared for you. It's a console-based trivia game which asks you about ten specific cases with a given function template declaration and a corresponding call. You will be asked about the deduced type of `T` and `t`.
Have fun!
***Note:*** Maybe you need to add the *Boost* library to the trivia project.


***Remarks:*** 
* You can have a look at the source code of the game. But, beware of the `QuestionGenerator.cpp` There is some preprocessor magic in it, which might be tough to understand if you are unfamiliar with it. It was necessary for overcoming the lack of reflection in C++. Don't worry, we won't ask you to know about such stuff in the exam though.
* The cases are hard-coded, but the actual answers are retrieved from the cases (under the assumption your compiler and boost do a decent job in figuring them out). If you feel you might have missed some of the cases due to the random selection for the trivia, you can use the `printAll` function to see all questions with the correct answers.

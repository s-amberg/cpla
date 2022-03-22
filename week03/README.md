# Exercises Week 3

Goals of this weeks exercises:

-   You solidify the understanding of type deduction in the trivia program



# 1. Introductory Question

Given the code for `BoundedBuffer` that you have implemented as Testat, we have two overloads of the `push` member function.

```
void push(T const &);
void push(T &&);
```

***Question:*** We have an overload of the `push` member function with a parameter of type `T&&`. Why is `T&&` here always an rvalue reference (and not a forwarding reference)?

***Note:*** There was the possibility to create a Forwarding Constructor. However, this actually is not a really good idea. Since the forwarding `T&&` overload, when `T` is a template parameter, is greedy. This results in copying non-const buffers prefering the Forwarding Constructor over the Copy Constructor, which does not work. A forwarding factory function does not suffer from this ambiguity.



# 2. Type Deduction Trivia

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



# 3. Forwarding Factory Function with One Single Argument
Create a factory function for your `BoundedBuffer` type that takes one argument of the element type. It shall create the `BoundedBuffer` and add the element to the buffer. *lvalue* arguments have to be passed as *lvalue* to the `push` function and *rvalues* have to be passed as *rvalues* to the `push` function.

We recommend to create this `make_buffer` function as static member function, as it is easier to specify the arguments of the `BoundedBuffer`.

***Note:*** We have prepared tests cases for this exercise as a project template. This project template contains all tests from the previous week and additional tests for this week's exercises. We recommend creating a new project from this template and copy your `BoundedBuffer.h` (and if you have your additional tests).

Here is an overview of the added test cases for part *a)*:
```cpp
void test_make_bounded_buffer_from_rvalue_argument_contains_one_element() {
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{});
  ASSERT_EQUAL(1, buffer.size());
}

void test_make_bounded_buffer_from_rvalue_argument_object_moved() {
  MemoryOperationCounter expected{1, 0, true};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{});
  ASSERT_EQUAL(expected, buffer.front());
}

void test_bounded_buffer_constructed_with_lvalue_argument_object_copied() {
  MemoryOperationCounter expected{0, 1, true};
  MemoryOperationCounter insertee{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(insertee);
  ASSERT_EQUAL(expected, buffer.front());
}

void test_bounded_buffer_constructed_with_const_lvalue_argument_object_copied() {
  MemoryOperationCounter expected{0, 1, true};
  MemoryOperationCounter const insertee{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(insertee);
  ASSERT_EQUAL(expected, buffer.front());
}
```

## ***Time for action:*** Your turn!
* Integrate the test cases above into your existing (or a copy of) *BoundedBuffer* project. You might need to make the type `MemoryOperationCounter` available to the context of the test cases. This type already exists in the tests of your BoundedBuffer, in `bounded_buffer_semantic_suite.cpp`.   
***Recommendation:*** Since the `MemoryOperationCounter` type is now used by multiple test suites it should reside in its own header file.

* Create a static template member function, which satisfies the tests above.
  * It must take a forward reference. This implies that template type deduction must happen. Subsequently, it must be a function template.
  * The factory function initializes the `BoundedBuffer` using the default constructor.
  * Additionally, pass the parameter of the factory function to a call of the `push` function.

***Warning for clang Users:*** We recognized that if you are using `clang` copy elision is pessimized by the return type `auto` for the `make_buffer` function. It is unclear to us why this happens, but it will lead to additional move operations in the `MemoryOperationCounter` objects.


# 4. Factory function with Multiple Arguments
As stated in part *a)* of the exercise, we actually want to pass an arbitrary number of arguments to that factory function. This mixes the topics of perfect forwarding and variadic templates. We have not explicitly covered this in the lecture, but you are encouraged to figure out on your own how to achieve this.
This functionality is expected to be included in the next testat. If you struggle to implement this, you can get a hint [here](https://gitlab.ost.ch/cxx/cpla/-/wikis/Exercise-Hint:-Factory-with-Multiple-Arguments).

***Hints:*** 
* Create a private helper member function `push_many` to push multiple elements to the `BoundedBuffer`. You need this function since it is easier to call a function recursively than a constructor.
* If too many arguments are supplied (more than the capacity of the buffer), throw an `std::invalid_argument` exception.

***Note:*** The test cases for this part of the exercise are already in the provided project, but have been disabled by comments.

Here is an overview of the added test cases for part *b)*:
```cpp
void test_make_bounded_buffer_from_two_rvalue_arguments_contains_two_elements() {
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
  ASSERT_EQUAL(2, buffer.size());
}

void test_make_bounded_buffer_from_two_lvalue_arguments_contains_two_elements() {
  MemoryOperationCounter element1{}, element2{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(element1, element2);
  ASSERT_EQUAL(2, buffer.size());
}

void test_make_bounded_buffer_from_too_many_elements_throws() {
  ASSERT_THROWS((BoundedBuffer<int, 1>::make_buffer(1, 2)), std::invalid_argument);
}

void test_make_bounded_buffer_from_two_rvalue_arguments_first_element_moved() {
  MemoryOperationCounter expected{1, 0, true};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});

  ASSERT_EQUAL(expected, buffer.front());
}

void test_make_bounded_buffer_from_two_rvalue_arguments_second_element_moved() {
  MemoryOperationCounter expected{1, 0, true};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
  ASSERT_EQUAL(expected, buffer.back());
}

void test_make_bounded_buffer_from_two_rvalue_arguments_first_element_copied() {
  MemoryOperationCounter expected{0, 1, true};
  MemoryOperationCounter lvalue{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(lvalue, MemoryOperationCounter{});
  ASSERT_EQUAL(expected, buffer.front());
}

void test_make_bounded_buffer_from_two_mixed_arguments_second_element_moved() {
  MemoryOperationCounter expected{1, 0, true};
  MemoryOperationCounter lvalue{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(lvalue, MemoryOperationCounter{});
  ASSERT_EQUAL(expected, buffer.back());
}

void test_make_bounded_buffer_from_two_rvalue_arguments_second_element_copied() {
  MemoryOperationCounter expected{0, 1, true};
  MemoryOperationCounter lvalue{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, lvalue);
  ASSERT_EQUAL(expected, buffer.back());
}

void test_make_bounded_buffer_from_two_mixed_arguments_first_element_moved() {
  MemoryOperationCounter expected{1, 0, true};
  MemoryOperationCounter lvalue{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, lvalue);
  ASSERT_EQUAL(expected, buffer.front());
}
```

---
keywords:
- c++
title: 'Rvalue References / Move Semantics'
---


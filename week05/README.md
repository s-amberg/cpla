# Exercise Week 5 - Iterators

In these exercises you will practice the implementation of you own iterator types. You will create an iterator for input streams, for creating a sequence of numbers and for your own `BoundedBuffer`.


# 1. TESTAT 2: BoundedBuffer with iterators (const and non-const) and allowing non-default-constructible elements (from last week)

In this exercise you will add iterators for to your `BoundedBuffer`.

Please form groups of 1-3 students for testat hand-in:
* Submission in ALF if it is up and running (https://alf.sifs0005.infs.ch), otherwise, by email.
* Specify if you have worked in a group.
* Content: `BoundedBuffer.hpp`
* You will get feedback as soon as possible
* Hand-in deadline: Tuesday 18. April 2023 23:59

## Iterator for Dynamic Bounded Buffer
Last week you have implemented a dynamic version of the bounded buffer. Finish that exercise first if you have not already completed it.

In this exercise you have to implement `begin` and `end` for your dynamic bounded buffer. They will return a random access iterator over the elements in the `BoundedBuffer`. As usual, `begin` shall return an iterator pointing to the first element in the buffer, i.e. the element that would be returned by `front()`. `end()` returns the corrsponding iterator that points behind the last element in the buffer, which is the element returned by `back()`. This requires your own iterator type, which can cope with the non-consecutive nature of the elements in your heap memory. The implementation of your iterator must be robust against invalid use, i.e. accesses outside the range specified by `begin` (inclusive) and `end` (exclusive) have to throw exceptions. It is not allowed to increment/decrement your iterator beyond these points (`begin`/`end`).

Create constant and non-constant iterators. Const iterators provide read-only access to the elements, while the non-const iterators allow changing the elements through the iterator. First, make both versions work! Then you can try to find a smart way to reuse the parts of your implementation and eliminate code duplication.

**Hints:**

* Define the iterator type as member of the bounded buffer.
* You are allowed to have two iterator classes (one for `const_iterator` and one for non-const `iterator`).
* Create corresponding type alias members in `BoundedBuffer`(`iterator` and `const_iterator`).
* If you struggle to figure out why certain tests are not green you may implement the `<<` operator for your iterator type in the test cases to visualize its state.
* Use `boost/operators.hpp` to shorten your implementation.

There is a template project with all the unit tests so far combined.

If you struggle to get it all up and running at once, try to satisfy one test case after another. Comment out all test contents first. Add the contents of the first test (start at the top of the tests), make it compile, make it green, repeat with the next tests.



# 2. Line Iterator (Not Testat)
In many of the exercises in the CPlusPlus module you had to process input line by line. It would have been convenient to have a line iterator in order to use standard algorithms instead of the `while` loops:
* Implement a line input iterator that that wraps an input stream.
* Use your line input iterator to improve your existing solution of one of the line-oriented CPlusPlus exercises.

You can use boost to simplify your solution.

**Hint:** The iterator will have a reference to an `std::istream` as member variable. See lecture slides if you struggle with the implementation.


# 3. Fibonacci Iterator (Not Testat)
In this first exercise you will implement a simple iterator similar to the iterator for integers from the lecture.

Instead of just counting your iterator will iterate through the Fibonacci numbers (https://en.wikipedia.org/wiki/Fibonacci_number). The given test cases expect your Fibonacci sequence to start with the value `0` for the zeroth number, `1` for the first number, `1` for the second number, and so on.

You need to implement the following members of the Fibonacci iterator:
* Constructor initializing the iterator with the `n`th element (default is `0`).
* `operator*` for accessing the current element (Fibonacci number) of the iterator.
* `operator==` to see whether two iterators have the same current element.
* `operator!=` the inverse of the `operator==`.
* `operator++` prefix and postfix increment.

We suggest you store the index (`i`th number) and not the Fibonacci value itself.

You find the prepared project containing the given unit tests [here](exercise_templates/w05_template_03_FibonacciIterator).

You can implement two versions of this iterator:
* Implement all operators yourself.
* Use the facilities of boost iterators (i.e. based on a counting iterator).

**Note:** Don't worry about efficiency in this exercise.




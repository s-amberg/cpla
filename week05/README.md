# Perfect Forwarding

Given the code for `BoundedBuffer` that you have implemented as Testat, we have two overloads of the `push` member function.

```
void push(T const &);
void push(T &&);
```

***Question:*** We have an overload of the `push` member function with a parameter of type `T&&`. Why is `T&&` always an rvalue reference (and not a forwarding reference)?

***Note:*** There was the possibility to create a Forwarding Constructor. However, this actually is not a really good idea. Since the forwarding `T&&` overload, when `T` is a template parameter, is greedy. This results in copying non-const buffers prefering the Forwarding Constructor over the Copy Constructor, which does not work. A forwarding factory function does not suffer from this ambiguity.


## a) Forwarding Factory Function with One Single Argument
Create a factory function for your `BoundedBuffer` type that takes one argument of the element type. It shall create the `BoundedBuffer` and add the element to the buffer. *lvalue* arguments have to be passed as *lvalue* to the `push` function and *rvalues* have to be passed as *rvalues* to the `push` function.

We recommend to create this `make_buffer` function as static member function, as it is easier to specify the arguments of the `BoundedBuffer`.

Here are some test cases for you:
```
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

### ***Time for action:*** Your turn!
* Integrate the test cases above into your existing (or a copy of) *BoundedBuffer* project. You might need to make the type `MemoryOperationCounter` available to the context of the test cases. This type already exists in the tests of your BoundedBuffer, in `bounded_buffer_semantic_suite.cpp`. ***Recommendation:*** Since the `MemoryOperationCounter` type is now used by multiple test suites it should reside in its own header file.
* Create a static template member function, which satisfies the tests above.
** It must take a forward reference. This implies that template type deduction must happen. Subsequently, it must be a function template.
** The factory function initializes the `!BoundedBuffer` using the default constructor.
** Additionally, pass the parameter of the factory function to a call of the `push` function.



##  b) Factory function with Multiple Arguments
As statet in part *a)* of the exercise, we actually want to pass an arbitrary number of arguments to that factory function. This mixes the topics of perfect forwarding and variadic templates. We have not explicitly covered this in the lecture, but you are encouraged to figure out on your own how to achieve this.

***Hint:*** Create a private helper member function `push_many` to push multiple elements to the `BoundedBuffer`. You need this function since it is easier to call a function recursively than a constructor.

```
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

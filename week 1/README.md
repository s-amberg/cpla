# Set Up Your Development Environment
 If you don't already have a development environment with [Cevelop](https://www.cevelop.com) and a recent compiler take care of this first. [Here](https://wiki.ifs.hsr.ch/CPlusPlus/ExW1) is a guide from CPl on how to do it.

## Update Your Compiler
* Install a recent version of GCC (version 8.2) or Clang (version 7.0.0).
* For Windows MinGW with a current GCC can be downloaded [here](https://nuwen.net/mingw.html).


## Update Cevelop
* Get the latest Cevelop version [here](https://www.cevelop.com)


## Install Stylechecker and Constificator
Cevelop offers helpful plug-ins, you should install:
* Install the Ctylechecker and Constificator plug-ins from the predefined update site (Help -> Install new software...)
* The required update site is preconfigured (https://www.cevelop.com/update/latest)


# Easy C++ Repetition Tasks
For the following tasks write test cases first!

1. Create a function that takes an `int` as parameter and returns the next value (`increment`).
``` cpp
int const value = 19;
auto const next = increment(value);
ASSERT_EQUALS(20, next);
```

2. Add an overload of `increment` that modifies the parameter as side-effect. Do you encounter any problems when calling increment in the presence of both overloads? Stick with the side-effect version for the following exercises.

``` cpp
int value = 19;
increment(value);
ASSERT_EQUALS(20, value);
```

3. Signed integers overflow is undefined behavior in C++. Make your function safe. If such an overflow would happen throw an exception instead of incrementing the value (`std::overflow_error`).
 
``` cpp
int const maxValue = std::numeric_limits<int>::max();
ASSERT_THROWS(increment(maxValue), std::overflow_error);
```

4. Change your `increment` to accept parameters of arbitrary type and increments them - given they support the prefix increment operator and `std::numeric_limits` provides a corresponding maximum value. Start your test cases with `double`.
 
``` cpp
double value = 1.5;
increment(value);
ASSERT_EQUALS(2.5, value);
```

5. Overflow for `unsigned` is well defined. Add an overload for this case that does not throw. Does it need to be a template specialization?

``` cpp
unsigned const maxValue = std::numeric_limits<unsigned>::max();
ASSERT_EQUALS(0, increment(maxValue));
```

6. Several overloads are required to cover all cases of `unsigned` type (i.e. `unsigned`, `unsigned long`) because the template has an exact match for the overload resolution unless you provide an overload for the specific type. Example: If you provide the overload for `unsigned long long` and call increment with an `unsigned` variable as argument the template will be chosen instead of the `unsigned long long` overload. Therefore, try an alternative approach to tackle overflows. Create a predicate (as template) `allow_overload` that returns `false` by default but can and should be specialized for `unsigned` types to be `true`. You can implement the predicate as variable, class or function template for that matter.

7. With all the template specializations for the different `unsigned` types there is still much code, at least it avoids duplication in the logic. As usual, the standard library can help. Have a look at `std::numeric_limits::is_integer` and the `is_unsigned` type trait. Can you implement your predicate with those?

8. Can you also pass an iterator to your `increment` function? You might experience different outcomes depending on your compiler. It might not be happy if you want to get `numeric_limits` for your iterator. Adapt your `increment` function to also have the capability to take a second parameter to have a user-provided limit. Your previous tests should still remain working. Therefore, add a default argument to that parameter. You probably used comparisons and a `-1` operation to your limit. Does this restrict the iterators you can use with `increment`?


# Fraction Type

Implement your own `Fraction` type that can represent fraction numbers more precisely than the `double` type.

* Your type will need to store the `numerator` and `denominator` as the largest possible integral type.
* Your type should be explicitly convertible to `double`
* Implement the basic arithmetic operations `+`, `-` (unary and binary), `*` and `/`. After every operation try to reduce `numerator` and `denominator`
* Add increment and decrement operators for your `Fraction` type.
* You shall use boost/operators to avoid writing unnecessary code yourself.
* Provide input and output operators 


# `dynArray` Repetition (Optional)
At the end of the C++ module you had an assignment in the exercises to create a `vector`-like container that features the capabilities to access its elements with negative indices (https://wiki.ifs.hsr.ch/CPlusPlus/ExW12). In the C++ Advanced module we will have an in-depth look at the implementation of bounded buffer container. We will expect that you are familiar and can easily implement containers like the `dynArray` example. Revisit the implementation of this task, implement it again or study the code carefully, in order to be properly prepared for the upcomming testat assignments. 
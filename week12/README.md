# Exercise 12 - Exception Safety and PIMPL

In this exercise...

* ... you will analyze your `BoundedBuffer` regarding exception-safety
* ... you implement the Pimpl Idiom


# 1. Exception Safety

## Standard Container Safety

Analyze the exception safety guarantees of `std::vector` on [cppreference](https://en.cppreference.com/w/cpp/container/vector).

## Exception Safety of `BoundedBuffer`

Analyze your `BoundedBuffer` implementation with regard to the exception safety guarantees we have discussed in the lecture.

* Which functions are `noexcept`?
* Which functions provide the strong guarantee?
* Which functions provide the basic guarantee?
* Which functions provide no guarantee?

## Guarantee Improvements

Try to implement every function in a way that it has at least the strong guarantee?

### Move Operations and `swap`

The move operations, i.e. move constructor and move assignment operations, usually rely on the `swap` member function. It would be desirable to have a `swap` member function that is unconditionally `noexcept`.

### Copy Operations

The copy operations, i.e. copy constructor and copy assignment operations, depend on the copyablilty of the element type. Test your buffer against the following requirements:
* The copy constructor is exception neutral and forwards exceptions thrown while copying the elements.
* Elements already copied have to be cleaned up properly.
* Copy assignment is exception neutral and forwards exceptions thrown while copying the elements.
* Elements already copied have to be cleaned up properly.
* If an exception occurs during copy assignment, the `this` object must not be modified! (Strong Guarantee)
** You can apply the copy-swap idiom to achieve this



# 2. Pimpl Idiom


## Pimpl with `std::unique_ptr`



## Advanced Optional: Pimpl Pointer


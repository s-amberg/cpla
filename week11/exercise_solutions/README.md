# Exercise 11 - Solution

# 1. Exception Safety

## Analyzing `std::vector`

The `std::vector` provides almost always at least the strong guarantee on all its member functions. Particularily interesting is the guarantee on operations that can resize the `std::vector` like `push_back`. If the element type does not have a `noexcept` move constructor the elements will be copied to ensure the guarantee! However, if the elements are not copyable and their move constructor could throw, the `std::vector` will try to move the elements with the "unsafe" move constructor. If that constructor throws the results are unspecified.

## `BoundedBuffer`

You should be able to implement the following member functions `noexcept`:

* Move Constructor
* Move Assignment Operator
* Destructor (If the elements are `noexcept` destructible
* `full()`
* `empty()`
* `size()`
* `capacity()`
* `swap()` - Even if the elements are not `noexcept` movable
* Iterator functions

You should be able to implement the following member functions providing the strong guarantee:
* Copy Assignment Operator - even if the elements are `noexcept` constructible you still have memory allocation that might throw. The Copy-Swap Idiom helps ensuring the guarantee.
* `push()` - if the elements provide the corresponding operation (move/copy) as `noexcept` this function can be `noexcept` too.
* `pop()` - if the elements are `noexcept` destructible, which they should be.
* `front()` - if the buffer is empty an exception is thrown
* `back()` - if the buffer is empty an exception is thrown



# 2. Pimpl Idiom

## Pimpl with `std::unique_ptr`

After applying the Pimpl Idiom you lose copyability and movability of the `Unicorn` objects. For retaining the movability the move operations (constructor and assignment operator) can be declared in `Unicorn` and then defined in the source file with their corresponding default implementation. This is similar to the handling of the destructor with `= default`. The copy operations cannot be implemented in this manner as the `std::unique_ptr` is not copyable at all. You would need to provide your own implementation that performs a deep copy.

If you would use an `std::shared_ptr` instead declaring the destructor, move and copy operations would not be required. The `Unicorn` objects would still be copyable. However, the copies would be shallow copies! Therefore, the semantics of `Unicorn` are changed. Furthermore, the counters used in an `std::shared_ptr` require memory, are atomic and have a small run-time overhead.

Recompilation: Only the `Unicorn.o` file should be recompiled after you have changed the return type of `calculateAltitude()` for the Pimpl version. While in the initial version all test objects need to be recompiled!

## Pimpl with Pimpl Pointer

With the `PimplPtr` the destructor and move operations need to be user declared. But the size of a `Unicorn` object increases from one pointer to two. Usually this is an increase from `8` to `16` byte.

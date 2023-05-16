# Exercise 11 - Exception Safety and Pimpl Idiom

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

Try to implement every function in a way that it has at least the strong guarantee. Is it possible?

### Move Operations and `swap`

The move operations, i.e. move constructor and move assignment operations, usually rely on the `swap` member function. It would be desirable to have a `swap` member function that is unconditionally `noexcept`.

### Copy Operations

The copy operations, i.e. copy constructor and copy assignment operations, depend on the copyablilty of the element type. Test your buffer against the following requirements:
* The copy constructor is exception neutral and forwards exceptions thrown while copying the elements.
* Elements already copied have to be cleaned up properly.
* Copy assignment is exception neutral and forwards exceptions thrown while copying the elements.
* Elements already copied have to be cleaned up properly.
* If an exception occurs during copy assignment, the `this` object must not be modified! (Strong Guarantee)
  * You can apply the copy-swap idiom to achieve this

# 2. Pimpl Idiom

In this exercise we use an adapted version of Felix Morgner's [Building Reusable Libraries](https://github.com/fmorgner/building-reusable-libraries/) examples. In the template project you find the `Unicorn` class, which is tested by the test cases in the `tests` directory. To demonstrate the benefit of the Pimpl Idiom we have created separate header and source files for every test case.

## Pimpl with `std::unique_ptr`
Adapt the `Unicorn` class to use the Pimpl Idiom. Hide all non-public members in the `UnicornImpl` class, which is local to the `Unicorn.cpp` file. Use a `std::unique_ptr` for the `pimpl` pointer.

* Which test cases cannot be compiled without adding explicit functionality to the `Unicorn` class after applying the Pimpl Idiom?
* Which special member functions' default implementation can be used to reenable their corresponding functionality?
* What are the advantages and disadvantages if you used an `std::shared_ptr` instead?
* You might have recognized that the `calculateAltitude()` member function has `int` as return type. Change the return type to `std::size_t` in the implementation with and without the Pimpl Unicorn. Can you spot a difference in the number of files that need to be compiled?


## Advanced: Pimpl Pointer (Optional)
Due to the requirement of the `std::unique_ptr` class template to be able to resolve the elements constructor at the point of declaration, unless an custom deleter is supplied, we need to dclare the destructor of `Unicorn`. However, it would also be possible to declare the `std::unique_ptr<class UnicornImpl, void(*)(class UnicornImpl *)>` with the explicit deleter function type as second template argument. This lifts the requirement of the destructor `~Unicorn` being known upfront.

* Create an alias template `PimplPointer<T>` that aliases `std::unique_ptr` for the given type and the deleter function, as mentioned above.
* Add a factory function `makeUniquePimpl()` that creates a `PimplPointer`. It takes any number of arguments and forwards them to the heap construction of the `T` element, which has to be stored in the `PimplPointer`. Additionally, as the second argument for the construction of the `PimplPointer`, a function has to be supplied for destroying the `T` object.
* Adapt `Unicorn` to use the `PimplPointer`.
* Which special member functions can now have their declaration removed?
* Did the size of a `Unicorn` change?


***Hints:***

* Heap allocation of `T` requires explicit call of `new`.
* For cleanup the `std::destroy_at` function can be used.


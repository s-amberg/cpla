# Compile-Time Computation

If you have not completed it yet, finish the testat exercise first!

Goals:
In these exercises you will...

* ... observe the effect of compile-time evaluation on the resulting executable binary.
* ... implement your own literal type
* ... implement compile-time member functions

## Compile-Time Hashing

**Context:** You have to write an application that requires a password for accessing higher privilege level for special configurations. This password shall be hard-coded into the binary.

It is probably not a smart idea to store passwords in a program in plain text. As it can be easily extracted from the binary's read only data section. An alternative might be to hash the password first and compare it against the hashed password provided by the user. Nevertheless, it is inconvenient to place password hashes directly into your source code. However, that is not necessary if you have a hashing function that can be called at compile-time.

We have prepared an example project that uses a constexpr function for hashing an input string: [here](week08/exercise_templates/w08_template_01_CompileTimeHashing)

Your task:

* Import the project in Cevelop or build it on console (`make`). It is a Makefile project that will compile two versions of a program. One will compute the hash of a password at runtime (`runtime.cpp`) the other will compute the hash of the password at compile-time (`compile_time.cpp`). The make file will also dump (with `objdump`) and scan the contents of the resulting binaries for the expected hash and the password.
* Check the output to see which implementation contains the password in plain text and which only contains the hash value.

## Literal Vector Type

Implement an N-dimensional `Vector` literal type. Don't worry, we don't want you to implement a STL-like container here. We rather want you to implement a simple type in the mathematical sense of vector, that can be used at compile-time. We have prepared a project template containing test cases [here](week08/exercise_templates/w08_template_02_VectorLiteralType).

The CUTE tests also contain `static_assert`s to show the compile-time capabilities of your `Vector`, at least for the cases where this is feasible. The CUTE `ASSERT`s in the test are for convenience reasons. Because a `static_assert` will not tell you what the actual and the expected values effectively were on failure, it is amenable to still have the CUTE framework for checking the values at run-time to see the comparison. You just need to comment the `static_assert` out.

**Note:** Since several test cases rely on class template argument deduction, Cevelop will mark the code as incorrect in many places, even though it might be correct! For this exercise rely on the compiler output instead.

Implement the following features:

* Allow creation of a vector with explicit class template arguments: `constexpr Vector<double, 1> v{1.0}`. 
  * Use an `std::array` for storing the `Vector`'s values.
  * You need to implement a constructor that is a variadic template to accommodate the arbitrary number of constructor arguments.
* Implement the subscript operator to access the individual components: `v[0]`
* Check that accessing an invalid index with the subscript operator throws an exception. Can you do this at compile-time?
* Overload the subscript operator that it distinguishes between `const` and non-`const` access. Can both be used in `constexpr` contexts?
* Implement the `==` and `!=` operators for comparing `Vector`s.
* Implement an output operator (`<<`) for printing `Vector`'s on an `std::ostream`. Can you implement that as `constexpr` function?
* Implement a `length()` member function that returns the length of a `Vector`.
* Implement a `scalarProduct()` function for calculating the scalar product of a `Vector`.
* **Difficult:** Implement class template argument deduction for `Vector`:
  * Implement a deduction guide for that constructor.
  * Can you restrict that it is not possible to supply different argument types for the construction? You ca use the predefined `are_all_same` predicate. It takes multiple type arguments and has the value `true` if all types are the same. You can apply it in an `std::enable_if_t` default template argument for the constructor.
  * Is it possible to check that the compilation fails when initializing a `Vector` with different types through a succeeding test?



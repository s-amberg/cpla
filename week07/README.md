# Compile-Time Computation


Goals:
In these exercises you will...

* ... observe the effect of compile-time evaluation on the resulting executable binary.
* ... implement your own literal type
* ... implement compile-time member functions
* ... implement your own user defined literal operators


## 1. Compile-Time Hashing

**Context:** You have to write an application that requires a password for accessing higher privilege level for special configurations. This password shall be hard-coded into the binary.

It is probably not a smart idea to store passwords in a program in plain text. As it can be easily extracted from the binary's read only data section. An alternative might be to hash the password first and compare it against the hashed password provided by the user. Nevertheless, it is inconvenient to place password hashes directly into your source code. However, that is not necessary if you have a hashing function that can be called at compile-time.

We have prepared an example project that uses a constexpr function for hashing an input string: [here](week07/exercise_templates/w07_template_01_CompileTimeHashing)

Your task:

* Import the project in Cevelop or build it on console (`make`). It is a Makefile project that will compile two versions of a program. One will compute the hash of a password at runtime (`runtime.cpp`) the other will compute the hash of the password at compile-time (`compile_time.cpp`). The make file will also dump (with `objdump`) and scan the contents of the resulting binaries for the expected hash and the password.
* Check the output to see which implementation contains the password in plain text and which only contains the hash value.
  * When checking the content you can use the `objdump` command, which is also included in the `Makefile`. Depending on your system and the binary format you will have to check different sections. Umcomment either of the `ODMPSECTION` variables in the `Makefile` to enable showing the corresponding section. Only one section can be displayed:
    ```make
    #ODMPSECTION = -j .rodata
    #ODMPSECTION = -j .rdata
    ODMPSECTION = -j .data
    ```

**Credits:** We have not implemented the compile-time hash functions ourselves, but use an existing implementation of [Chocobo1](https://github.com/Chocobo1/Hash), that is published under GPL3.0.


## 2. Compile-Time Fibonacci

**Important:** You have to increase the constexpr cache depth if you use a recent version of GCC/MinGW for this exercise, when your implementation is a naive recursion. Use the following flag to enable caching of function results: `-fconstexpr-cache-depth=50`

1. Implement computing the `n`th fibonacci number in the following means as compile-time computation:

* a) With a constexpr function `fibo(unsigned)`
* b) With a variable template `fibo_v<unsigned>`. ***Hint:*** If you are using Cevelop, there might be an issue with parsing an expression containing varible templates. Therefore, you might want to put a reference to a varaible template in parentheses, to avoid ambiguities in the parse: `(fibo_v<n-2>)`.
* c) With a user defined literal operator `5_fibo` that is evaluated at compile-time
* d)  Measure and compare the compilation and run-time for computing the 46th fibonacci number. Does it make a difference regarding compilation time if the signature is changed to `fibo(unsigned const & n)`? For the change of the parameter type to `unsigned const & n` you might need to add an additional compile flag: `-fconstexpr-ops-limit=100000000000000`

2. Implement similar constructs to the above that return an `std::array<int, n>` filled with the `n` first fibonacci numbers instead. Unfortunately, even though `std::array` is a literal type in C++17, its comparison operations are not `constexpr`. First implement a function for comparing the content of `std::array` at compile time: `arrayEquals`.  

* a) With a constexpr template function `fiboa` that takes the size of the array as template parameter. E.g. fiboa<5>()
* b) With a variable template `fiboa_v<int>`
* c) ***Optional (for experts):*** A user defined literal operator `10_fiboa` (returns an `array<int, 10>`). You will need to create infrastructure to parse the value of the literal.


## 3. Literal Vector Type

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
  * Can you restrict that it is not possible to supply different argument types for the construction? You can use the predefined `are_all_same` predicate. It takes multiple type arguments and has the value `true` if all types are the same. You can apply it in an `std::enable_if_t` default template argument for the constructor.
  * Is it possible to check that the compilation fails when initializing a `Vector` with different types through a succeeding test?

## 4. (Optional): Conversion with Tags and Traits

Implement a `temperature` literal type, similar to the `Speed` type you have seen in the lecture. The `Temperature` type shall be taggable with the units `Kelvin`, `Celcius` and `Fahrenheit`.

* Add the required tag types to the namespace `units::tags`.
* Specify the `Temperature` class template that stores the temperature in a `double` value.
* Implement comparison operations for the `Temperature` template for comparison with other objects of the same template instance (`==`, `!=`, `<`, `>`, `<=` and `>=`).
* Implement arithmetic operations for the `Temperature` template (`+`, `-`) - unary and binary.
* Implement the `ConversionTraits` class template with a `convert` member function and add a specialization for every possible conversion. You can lookup the conversion formula on the web. ***Note:*** We have not covered this in the current lecture. But you can look it up in the lecture example code for `Speed` literals and apply it for `Temperature`.
* Implement a `temperatureCast` function template that delegates conversion to the `ConversionTraits` template.
* Add comparison operation templates to allow comparison of objects of arbitrary `Temperature` instances.
* Add user defined literal operators (`_K`, `_C`, `_F`) to the `unit::literals` namespace.

***Note:*** The project template for this exercies does not contain test cases for all operations above.


## 5. (Optional): Compile-Time Maze

In the lecture examples we have implemented the generation of mazes at compile-time. Example


```
+---+---+---+---+---+
|                   |
+   +   +   +---+   +
|   |   |       |   |
+---+   +   +   +   +
|       |   |   |   |
+---+---+   +   +   +
|           |   |   |
+   +---+   +---+---+
|   |               |
+---+---+---+---+---+

```

The two projects solve the following problems completely at compile-time:
- Generate pseudo random numbers. Implemented with a slightly reduced version of the linear congruential generator implemented by `java.util.Random`. It should actually produce the same random numbers.
- Seeding the RNG by the time value provided by `__TIME__` back to seconds (unfortunately, `std::hash` is not available at compile-time). The seed is generated at compile-time and requires re-compilation to change.
- Generating the maze using the Sidewinder algorithm explained in Jamis Buck's book "Mazes for Programmers". Actually, the whole idea is of generating and solving mazes is from this book. In short the algorithm processes every row of the maze by (1) creating runs - randomly connecting horizontal adjacent cells and (2) connecting each run to the row above (if any). This creates so called _perfect mazes_, which have exactly one path connecting two cells (i.e. no loops).
- Generating the textual representation (see above)

The only task left for the programm is to print the resulting maze.

### Study the code

Have a look at the implementation and see how the individual parts are solved at compile-time.

### Shortest Path

The book also covers implementing the shortest path algorithm by Dijkstra. I.e. calculating the distance from every field to a specific designated field, for example at `0/0`. We have not provided a solution so far, but if you like you can try to implement that and even try to do it at compile-time.

Example solution:


```
+---+---+---+---+---+
| 0   1   2   3   4 |
+   +   +   +---+   +
| 1 | 2 | 3   4 | 5 |
+---+   +   +   +   +
| 4   3 | 4 | 5 | 6 |
+---+---+   +   +   +
| 7   6   5 | 6 | 7 |
+   +---+   +---+---+
| 8 | 7   6   7   8 |
+---+---+---+---+---+

```

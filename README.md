# Module: C++ Advanced

This repository hosts the contents for the C++ Advanced (CPlA) module at
OST. Current run **Spring Semester 2024**.

## Goal

In the course of this module students learn usage and understanding of
advanced features of modern C++. The topics of this course will cover:

-   Advanced concepts and language features
-   Functional and generic programming at run- and compile-time
-   Usage of advanced libraries, for example Boost libraries
-   A view behind the curtains of the C++ language standardization
-   Outlook to upcomming C++ features (C++23, ...)

Code examples in the lecture and exercises target the current C++
standard, also known als C++20. A pre-version of the language standard
can be found
[here](https://isocpp.org/files/papers/N4860.pdf).
This working draft lacks only minor editorial fixes compared to the
official standard.


## Visual Studio Code

We recommend to use [Visual Studio Code](https://code.visualstudio.com/) for our C++ courses.

## Compiler

We configured a devcontainer with the complete environment you need. Running the container (Docker) and cloning the repository should provide everything you need. It is to be checked regarding the exercises in the weeks towards the end of the semester.

Otherwise:
- Windows: Msys2 Installation with GCC 13
- MacOS: Clang 16 works with limitations in the area of range algorithms. GCC would be better but suffers from linker crashes on ARM-based platforms.
- Linux: Clang 17 or GCC 13 work both

## Test Framework

Before we used [CUTE](https://www.cute-test.com/) but in the current run we try [Catch2](https://github.com/catchorg/Catch2). We decided to change this as CUTE needed to get closer to Google Test and Catch2 regarding test macros in order to work properly with VS Code extensions. Still the support for the latter two is better integrated. Furthermore, no `main()` is needed to write tests, as this can be configured in CMake dependencies.


## Lecture Plan and Resources

**Videos:** There is a [SwitchTube channel](https://tube.switch.ch/channels/2a2692d0) that contains the prerecorded lectures from FS20 or FS21. Although we do not intend to change the content significantly, we still don't guarantee that the videos contain exactly te same content as the live-lecture in FS22. They can be considered alternatives if someone cannot attend the live-lecture or as repetition for preparing the exam.

| Week | Lecture                | Exercise                                                                                | Topics                                                 | Remarks        |
|------|------------------------|-----------------------------------------------------------------------------------------|--------------------------------------------------------|----------------|
| 01   | [L1](week01) | [E1](week01/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week01.pdf))   | Introduction / C++ Recap                              |                |
| 02   | [L2](week02) | [E2](week02/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week02.pdf))   | Rvalue References / Move Semantics / Copy Elision     | **Testat 1**   |
| 03   | [L3](week03) | [E3](week03/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week03.pdf))   | Type Deduction / Perfect Forwarding                   |                |
| 04   | [L4](week04) | [E4](week04/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week04.pdf))   | Explicit Heap Memory Management                       | [CppCon-Talk about Pointer](https://www.youtube.com/watch?v=rqVWj0aVSxg)               |
| 05   | [L5](week05) | [E5](week05/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week05.pdf))   | Iterators / Tags for Conversion                       | **Testat 2**   |
| 06   | [L6](week06) | [E6](week06/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week06.pdf))   | Advanced Templates / SFINAE                           |                |
| 07   | [L7](week07) | [E7](week07/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week07.pdf))   | Compile-Time Computation / Literal Types / UDL        |                |
|      | Arbitrary Break |                                                                            |                                                       | **No Lecture** |
| 08   | [L8](week08) | [E8](week08/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week08.pdf))   | Multi-Threading / Mutexes                             | **Testat 3** <br/> [CppCon-Talk about Concurrency](https://www.youtube.com/watch?v=F6Ipn7gCOsY)   |
| 09   | [L9](week09) | [E9](week09/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week09.pdf))   | Memory Model / Atomics                                |                |
| 10   | [L10](week10) | [E10](week10/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week10.pdf)) | Networking (ASIO)                                     |                |
|      | Arbitrary Break |                                                                            |                                                       | **No Lecture** |
| 11   | [L11](week11) | [E11](week11/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week11.pdf)) | Advanced Library Design: Exception Safety / PIMPL     |                |
| 12   | [L12](week12) | [E12](week12/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week12.pdf)) | Hourglass Interfaces                                  |                |
| 13   | [L13](week13) | [E13](week13/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week13.pdf)) | Build Systems                                         |                |
| 14   | [L14](week14) | [E14](week14/README.md) ([PDF](http://cxx.pages.gitlab.ost.ch/cpla/week14.pdf)) | WebAssembly & C++                                     |                |



### Useful Links

MS Teams for the CPlA module:
* [MS Teams Link](https://teams.microsoft.com/l/team/19%3auUkXXiUMQ3kUNqZh7ArVPyi7Tu40y9yrbuC0RmdF8Zk1%40thread.tacv2/conversations?groupId=9bdd64ad-d818-4a1c-b173-cf26ec062f46&tenantId=a6e70fa3-1c7a-4aa2-a25e-836eea52ca22)
We might make announcements here and there is a channel where you can ask for help and questions.


Language References:
* CPP Reference: https://www.cppreference.com/
* CPlusPlus.com: http://www.cplusplus.com
* MSDN Language Reference: https://docs.microsoft.com/en-us/cpp/cpp/cpp-language-reference
* MSDN Standard Library Reference: https://docs.microsoft.com/en-us/cpp/standard-library/cpp-standard-library-reference
 
Online Compilers:
* Godbolt: https://godbolt.org/
* Online GDB: https://www.onlinegdb.com/online_c++_compiler
* Wandbox: https://wandbox.org/

Links from the Lecture:
* Structured Bindings: https://skebanga.github.io/structured-bindings/
* Problems with Move Semantics (You Tube): https://www.youtube.com/watch?v=PNRju6_yn3o
* Rvalue References and Move Semantics: http://thbecker.net/articles/rvalue_references/section_01.html
* Too Perfect Forwarding: https://akrzemi1.wordpress.com/2013/10/10/too-perfect-forwarding/
* Fun with Blinky (You Tube): https://www.youtube.com/watch?v=6pmWojisM_E
* Reading Declarations: https://cdecl.org/
* Overhead of Dynamic Dispatching: http://eli.thegreenplace.net/2013/12/05/the-cost-of-dynamic-virtual-calls-vs-static-crtp-dispatch-in-c
* Long Compile-Times with Template Meta Programming: http://cpptruths.blogspot.ch/2005/11/c-templates-are-turing-complete.html

IDE and Compilers:
* VS Code: https://code.visualstudio.com/
* Cevelop: https://www.cevelop.com
* MinGW (MSYS2): https://www.msys2.org/
* CMake: https://cmake.org/

Libraries:
* Catch2: https://github.com/catchorg/Catch2
* CUTE: https://www.cute-test.com/
* Boost Library: https://www.boost.org/
* Boost Units: https://www.boost.org/doc/libs/1_69_0/doc/html/boost_units/Units.html
* ASIO: https://think-async.com/Asio/ 
* SFML: https://www.sfml-dev.org/

Collection of C++ Resources:
* https://github.com/MattPD/cpplinks

Exercises with Solutions
* The Modern C++ Challenge (Available only at OST internally): https://ebookcentral.proquest.com/lib/fh-ostschweiz/detail.action?docID=5400397&query=bancila

---
keywords:
- c++
title: 'C++ Advanced: Module overview'
---


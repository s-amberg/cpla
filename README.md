# Module: C++ Advanced

This repository hosts the contents for the C++ Advanced (CPlA) module at
HSR. Current run **Spring Semester 2019**.

## Goal

In the course of this module students learn usage and understanding of
advanced features of modern C++. The topics of this course will cover:

-   Advanced concepts and language features
-   Functional and generic programming at run- and compile-time
-   Usage of advanced libraries, for example Boost libraries
-   A view behind the curtains of the C++ language standardization
-   Outlook to upcomming C++ features (C++20, ...)

Code examples in the lecture and exercises target the current C++
standard, also known als C++17. A pre-version of the language standard
can be found
[here](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4659.pdf).
This working draft lacks only minor editorial fixes compared to the
official standard.

## Skripteserver

Contents and resources not intended for public access are stored on an
[internal "skripte"
server](https://skripte.hsr.ch/Informatik/Fachbereich/C++_Advanced/CplA/)
at HSR.

## Cevelop

We recommend to use the [Cevelop](https://www.cevelop.com) for our C++
courses. While it is possible to use other IDEs, only Cevelop is:

-   platform independent
-   free to use
-   provides suitable support for unit testing with
    [CUTE](https://www.cute-test.com)
-   has quality-of-life features like assisted inclusion of standard
    library headers
-   hints about common programming mistakes
-   and can visualize template instances

## Lecture Plan and Resources

| Week | Lecture                | Exercise                                                                               | Topics                                                 | Remarks        |
|------|------------------------|----------------------------------------------------------------------------------------|--------------------------------------------------------|----------------|
| 01   | [L1](week01)           | [E1](week01/README.md) ([PDF](/../-/jobs/artifacts/master/file/week01.pdf?job=week01)) | Introduction / C++ Recap                               |                |
| 02   | [L2](week02)           | [E2](week02/README.md) ([PDF](/../-/jobs/artifacts/master/file/week02.pdf?job=week02)) | New Features in C++17                                  |                |
| 03   | [L3](week03)           | [E3](week03/README.md) ([PDF](/../-/jobs/artifacts/master/file/week03.pdf?job=week03)) | Rvalue References / Move Semantics / Copy Elision      |                |
| 04   | [L4](week04)           | [E4](week04/README.md) ([PDF](/../-/jobs/artifacts/master/file/week04.pdf?job=week04)) | Type Deduction                                         | **Testat 1**   |
| 05   | [L5](week05)           | [E5](week05/README.md) ([PDF](/../-/jobs/artifacts/master/file/week05.pdf?job=week05)) | Perfect Forwarding                                     |                |
| 06   | [L6](week06)           | [E6](week06/README.md) ([PDF](/../-/jobs/artifacts/master/file/week06.pdf?job=week06)) | Explicit Heap Memory Management                        |                |
| 07   | [L7](week07)           | [E7](week07/README.md) ([PDF](/../-/jobs/artifacts/master/file/week07.pdf?job=week07)) | Advanced Templates / Iterators                         | **Testat 2**   |
| 08   | [L8](week08)           | [E8](week08/README.md) ([PDF](/../-/jobs/artifacts/master/file/week08.pdf?job=week08)) | Compile-Time Computation / Literal Types / SFINAE      |                |
| 09   | [L9](week09)           | [E9](week09/README.md) ([PDF](/../-/jobs/artifacts/master/file/week09.pdf?job=week09)) | Traits for Conversion / User Defined Literals          |                |
| 10   | L10                    |                                                                                        | Multi-Threading / Networking (ASIO)                    |                |
| 11   | L11                    |                                                                                        | Memory Model                                           | **Testat 3**   |
| 12   | L12                    |                                                                                        | Exception Safety / Advanced Library Design             |                |
| 13   | L13                    |                                                                                        | C++ Standardization (Insights by a Committee Member)   |                |
| 14   | L14                    |                                                                                        | Build Systems                                          |                |
| 15   | Ascension Day          |                                                                                        |                                                        | **No Lecture** |

### Useful Links

Language References:
* CPP Reference: https://www.cppreference.com/
* CPlusPlus.com: http://www.cplusplus.com
* MSDN Langauge Reference: https://docs.microsoft.com/en-us/cpp/cpp/cpp-language-reference
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
* Cevelop: https://www.cevelop.com
* MinGW (from STL): https://nuwen.net/mingw.html

Libraries:
* Boost Library: https://www.boost.org/
* Boost Units: https://www.boost.org/doc/libs/1_69_0/doc/html/boost_units/Units.html
* ASIO: https://think-async.com/Asio/ 

Collection of C++ Resources:
* https://github.com/MattPD/cpplinks

---
keywords:
- c++
title: 'C++ Advanced: Module overview'
---


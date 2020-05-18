# Module: C++ Advanced

This repository hosts the contents for the C++ Advanced (CPlA) module at
HSR. Current run **Spring Semester 2020**.

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

**Videos:** There is a [SwitchTube channel](https://tube.switch.ch/channels/2a2692d0) that contains lecture videos for remote learning.

| Week | Lecture                | Exercise                                                                                | Topics                                                 | Remarks        |
|------|------------------------|-----------------------------------------------------------------------------------------|--------------------------------------------------------|----------------|
| 01   | [L1](week01)           | [E1](week01/README.md) ([PDF](/../-/jobs/artifacts/master/file/week01.pdf?job=week01))  | Introduction / C++ Recap                               |                |
| 02   | [L2](week02)           | [E2](week02/README.md) ([PDF](/../-/jobs/artifacts/master/file/week02.pdf?job=week02))  | Rvalue References / Move Semantics / Copy Elision      | **Testat 1**   |
| 03   | [L3](week03)           | [E3](week03/README.md) ([PDF](/../-/jobs/artifacts/master/file/week03.pdf?job=week03))  | Type Deduction / Perfect Forwarding                    |                |
| 04   | [L4](week04)           | [E4](week04/README.md) ([PDF](/../-/jobs/artifacts/master/file/week04.pdf?job=week04))  | Explicit Heap Memory Management                        |                |
| **No lessons in the week of 16. March!** |
| 05   | [L5](week05) [Video](https://tube.switch.ch/videos/637072ca)           | [E5](week05/README.md) ([PDF](/../-/jobs/artifacts/master/file/week05.pdf?job=week05))  | Iterators / Tags for Conversion                        | **Testat 2**   |
| 06   | [L6](week06)           | [E6](week06/README.md) ([PDF](/../-/jobs/artifacts/master/file/week06.pdf?job=week06))  | Advanced Templates / SFINAE                            |                |
| 07   | [L7](week07)           | [E7](week07/README.md) ([PDF](/../-/jobs/artifacts/master/file/week07.pdf?job=week07))  | Compile-Time Computation / Literal Types / UDL         |                |
|      | Easter Break           |                                                                                         |                                                        | **No Lecture** |
| 08   | [L8](week08)           | [E8](week08/README.md) ([PDF](/../-/jobs/artifacts/master/file/week08.pdf?job=week08))  | Multi-Threading / Mutexes                              | **Testat 3**   |
| 09   | [L9](week09)           | [E9](week09/README.md) ([PDF](/../-/jobs/artifacts/master/file/week09.pdf?job=week09))  | Memory Model / Atomics                                 |                |
| 10   | [L10](week10)          | [E10](week10/README.md) ([PDF](/../-/jobs/artifacts/master/file/week10.pdf?job=week10)) | Networking (ASIO))                                     |                |
| 11   | [L11](week11)          | [E11](week11/README.md) ([PDF](/../-/jobs/artifacts/master/file/week11.pdf?job=week11)) | Advanced Library Design: Exception Safety / PIMPL      |                |
| 12   | [L12](week12)          | [E12](week12/README.md) ([PDF](/../-/jobs/artifacts/master/file/week12.pdf?job=week12)) | Hourglass Interfaces                                   |                |
| 13   | [L13](week13)          | [E13](week13/README.md) ([PDF](/../-/jobs/artifacts/master/file/week13.pdf?job=week13)) | Build Systems                                          |                |


### Useful Links

Discord for C++ Modules:

* [Invite Link](https://discord.gg/vrFXkEJ)


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
* CMake: https://cmake.org/

Libraries:
* Boost Library: https://www.boost.org/
* Boost Units: https://www.boost.org/doc/libs/1_69_0/doc/html/boost_units/Units.html
* ASIO: https://think-async.com/Asio/ 
* SFML: https://www.sfml-dev.org/

Collection of C++ Resources:
* https://github.com/MattPD/cpplinks

Exercises with Solutions
* The Modern C++ Challenge (Available only at HSR internally): https://ebookcentral.proquest.com/lib/fh-ostschweiz/detail.action?docID=5400397&query=bancila

---
keywords:
- c++
title: 'C++ Advanced: Module overview'
---


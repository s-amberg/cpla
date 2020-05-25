# Exercise 13 - Build Systems

In this exercise...

* ... you will set up CMake to be used on your system
* ... create a *CMake* setup for your `BoundedQueue`
* ... adjust your project layout to follow the best-practices shown in the lecture

# 1. Setting up CMake

Depending on your OS, install *CMake* on your system.
If you are going to Cevelop for the exercises, also install the *Ninja* build tool.

## Installation on Windows

Download the *CMake* installer from the [CMake website](https://cmake.org/download/). During installation, make sure to select the option to add *CMake* to your PATH!
Follow [these instructions](https://github.com/rwols/CMakeBuilder/wiki/Ninja-for-Windows-Installation-Instructions) to make sure that Ninja is in your environments path.

## Installation on macOS

You should be able to install *CMake* and *Ninja* via Homebrew.

## Installation on Linux

Install *CMake* and *Ninja* using your distribution's package manger.

## Testing your installation

After installing *CMake*, test that your setup worked using the `w14_01_my_app_cmake` project from the `lecture_templates` folder:

To test on the Terminal:

1. Using your terminal, change the working directory to your copy of the example.
2. Create a new directory called `build` inside the example directory
3. Enter this new directory.
4. Invoke `cmake ..` to create a new set of build scripts for the project. ***NOTE:*** On Windows, you will have to add the command line parameter `-G"MinGW Makefiles"` to ensure *CMake* picks up the correct compiler!
5. Invoke `cmake --build .` to build the project.

If you prefer to work with an IDE, check you IDE's instructions (refer to the lecture if you are working with Cevelop) on how to import a CMake project.

If everything worked successfully, you should be left with an application called `my_app` (or `my_app.exe` if you are on Windows) that should produce the message "This is my awesome app!" when run.

# 2 CMake for `BoundedQueue`

Use the same sources as in the previous exercise, but this time around, your goal is to provide a *CMake* configuration for your project. Create a file called `CMakeLists.txt` in the root directory of your source code containing a configuration that covers the following points:

* Make sure that C++ is the only enabled language for your project.
* Again, we are using C++17. Set the correct *CMake* target compile features.
* We want to use standard C++. Make sure that non-standard extensions are disabled
* Remember to tell *CMake* that the `cute` directory contains header files required by our source code.
* Add an executable called `BoundedQueueTests` that is build using all `.cpp` files in the project.
* Ensure that your executable is linked against the `pthread` library.

Build your project using the commands discussed in the lecture.

## 2++ (Optional)

In the lecture, you have seen that *CMake* also ships with *CTest*. Extend your `CMakeLists.txt` so that you can use the `ctest` command to run your tests.

# 3 Project Structure

Having all files in a single directory gets messy fast. Adjust the directory hierarchy of your project according the guidelines presented in the lecture. Here are some things to keep in mind:

* You will need to adjust your `CMakeLists.txt` accordingly to reflect the new paths your resources live at.
* Headers, sources and third party libraries only used for tests should live in the according subdirectories inside the `test` folder.

Make sure your project still builds successfully.

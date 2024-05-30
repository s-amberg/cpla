# Exercise 12 - Hourglass Interfaces

In this exercise...

* ... you will implement a C API for a library we provide you with
* ... use this C API in a Java application using JNA


# 0. Important Notes and Preparation

***Warning:*** The devcontainer is not setup for this exercise, as it requires running a Java GUI (you could implement an alternative version of the Java part, that just serializes the image into a file). To run the lecture example (which does not need a GUI) you need to install a JDK first on it using `pacman` (or `apt` if you use a debian-based image). Reconfiguring CMake is required after the Java installation as these exercises are not compiled if it is not present.

You might encounter some problems when trying to use you dynamic libary, so make sure:

* That your artifact name is correct.
* That your shared library artifact is at the right location for the JNA loader to find it
* That your function and struct member types match between the C API and Java-land.
* If you are starting fresh (not using our templates), that you build a **shared** library, not a **static** one.

After compiling, you should be able to run the lecture example.
To do so, go to the `java` folder in the `build` folder, and run the following command:

```bash
java -Djna.library.path=. -cp w12_02_jna_app.jar:jna-5.5.0.jar ch.ost.cpla.CplaJNA
```

# 1. Java Julia Viewer

We have prepared a template for a Julia set rendering library, as well as a Java application that uses this library.
The library is used to render a Julia set as a bitmap image in memory, while the Java application's job is to display that image.
Your job is to implement a C interface for the library consisting of the following functions and types

* A type-alias `image` for the opaque pointer type `struct Image *`
* A function `image createImage(uint32_t)` to instantiate a new bitmap image
* A function `void disposeImage(image)` to destroy such an image
* A function `int32_t getSize(image)` to retrieve the size of an image
* A function `char * dump(image, int *)` to get access to the in-memory bitmap data of an image
* A function `void disposeBitmapData(char *)` to clean up the memory retrieved using `dump`
* A plain struct `window` with three `double` members `x`, `y`, and `z`
* A function `void render(image, window, double exponent, double real, double imaginary, int)` to render a Julia set into a previously created image

Don't forget to make sure the function and struct names don't get mangled by the compiler!

On the Java side, you have to implement an appropriate interface that loads the library and provides suitable types and functions to use library.

After compiling, you should be able to run the application.
To do so, go to the `java` folder in the `build` folder, and run the following command:

```bash
java -Djna.library.path=. -cp w12_sol01_julia_jna_app.jar:jna-5.5.0.jar  ch.ost.cpla.JuliaJNA
```

Substitute `sol01` with `ex01` to run the artifact compiled from the template.

# 2. Error Handling (Optional)

In the current version of the library and application, we have ignored any error handling.
Extend the library and the application using suitable error handling techniques

# 3. Julia for Other Languages (Optional)

Choose your favorite language (besides C++ :)) to implement the "upper cone" of the hourglass.
Use your implementation to write an application that uses the Julia library in some fashion.
Check the documentation of your language to find out how you can use C libraries.

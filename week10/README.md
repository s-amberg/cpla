# Exercise 10 - Threading and Asynchronous IO

In this exercise...

* ... you get familiar with the thread API of C++
* ... you implement basic asynchronous communication using ASIO
* ... you realize the communication logic in an existing application


# 1. Basic Threading

## a) Thread IDs
Create a simple application that starts three threads:

* One thread shall be created with a functor
* One thread shall be created with a free function
* One thread shall be created with a lambda

Each thread prints its ID (`std::this_thread::get_id()`) on `std::cout`.

Since it is discouraged to use `std::cout` directly in your functor, function and lambda, each should have a `std::ostream & out` parameter. If you want to pass `std::cout` through the `std::thread` constructor, you have to wrap the argument in an `std::ref` on the call-site.

## b) Measure Speedup
In the template you have an implementation of a program that counts the prime numbers in a given range (`countPrimes` function). Parallelize the computation using multiple threads in `countPrimesParallel`.

***Note:*** Be aware, that each thread must only access his entry of the `results` array and that the `main`thread must only access those results after the threads have been joined.

What speedup can you achieve?

# 2. Standalone Asynchronous IO (Chat Client)

We have prepared projects using ASIO to implement a chat client-server application. It is the example ASIO chat client-server application from [here](https://think-async.com/Asio/asio-1.12.2/doc/asio/examples/cpp11_examples.html)

Preparation:
 * You need to download the ASIO library from [here](https://think-async.com/Asio/). You won't need to compile and install the library, but you need to add the include path of the extracted location to your project: `<asio-directory>/include`
 

***Note:*** If you are on Windows you need library dependencies that depend on the Windows platform! The follwing libraries are required for this exercise: `ws2_32` and `wsock32`.

Get the project compiled. Besides the library dependencies you need to be aware, that there are two `main` functions in the project. We have created two build configurations: `Debug (Server)` and `Debug (Client)` which each have the other source file excluded.

It is easier to follow the message flow if you don't run all executables from the IDE. You can run them in separate terminal windows. The server will not feature any output at all. The client's messages will be distributed among all connected clients.

If you wan't the details about the source code, you can browse the API reference of [ASIO Documentation](https://think-async.com/asio/asio-1.12.2/doc/).


# 3. Connect Four Game with SFML
Your task is to finish the implementation task for the  Connect Four Game's `ServerPeer`, see `peer/ServerPeer.h` for detailed instructions.

The idea is that both a client and a server each run their game instance and communicate asynchronously using the ASIO Library. The UI is created using the SFML library (see [SFML](https://www.sfml-dev.org/)) and runs in the main thread, while the socket communication is done in a separate thread.

When running the game one side will wait for the other to make a move and update their state accordingly and then do their turn while the other waits.

The server waits and accepts incoming clients on the provided port and the hosts address.

The client to connect to the provided endpoint (server-address and port) and starts the game on success.

## Building the project
Cevelop: Use the appropiate build configuration for you platform `Debug (Linux)` and `Debug (Windows)` that will link the correct libraries needed for the game to work.

***Note:*** Make sure that you have also opened (and on Linux built) the `SFML` project (found under `week10/exercise_libs/SFML/`) to allow the linking to succeed.

The following libraries are needed and must be present for the linking to succeed.

* Windows: `opengl32`, `winmm`, `gdi32`, `freetype`, `ws2_32`, `wsock32` and `z`
* Linux: `freetype`, `X11`, `GL`, `udev` and `Xrandr`.

Further the different SFML libraries are needed for both platforms, see the SFML Libraries section. ASIO (no boost required) is used as a header only library and already included, see the ASIO Library section.

## ASIO Library
The asio library is already part of the template inside the `include` folder.

## SFML Libraries
The prepared project contains prebuild SFML libraries for Windows. Those SFML libraries have been build with MinGW from [STL](https://nuwen.net/mingw.html), i.e. GCC version 8.2. This distribution contains all the required dependencies. On other platforms get the SFML libraries via your package manager.

Alternatively, you can build the libraries on your own: See the included script file (Linux). It is also possible to get the sources for [SFML](https://www.sfml-dev.org/) and build the libraries yourself. It requires `cmake` and `make`. This should work on all plattforms. However, we suggest you build the static debug versions of the libraries.

## How to play

To play the game the executable can be run in different modes depending ont the passed arguments.

* Zero arguments: A local game is started. You can play both sides in the same window locally.
* One arguments (port): This starts the game in the server mode listening on the specified port.
* Two arguments (server-address port): This starts the game in the client mode, which will attempt to connect to the given ip and port.

In either client or server mode the game waits for the other side to join it. You can also run both locally by specifing the same port and using `localhost` or `127.0.0.1` as the server address.

***Note:*** You can use different `Run Configurations` to launch the different modes directly (see `Run Configurations...` -> `Arguments`).

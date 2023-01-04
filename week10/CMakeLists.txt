cmake_minimum_required(VERSION 3.19)

project(w10 LANGUAGES CXX)

find_package("Threads")

# Libraries

add_library("asio" INTERFACE)
target_include_directories("asio" SYSTEM INTERFACE
    "${PROJECT_SOURCE_DIR}/exercise_libs/asio/include"
)

if(WIN32)
    target_link_libraries("asio" INTERFACE
        "ws2_32"
        "wsock32"
    )
endif()


week_library(NAME "simple_http"
    SOURCES
    exercise_libs/simple_http/src/request.cpp
    exercise_libs/simple_http/src/header.cpp
    exercise_libs/simple_http/src/message.cpp
    exercise_libs/simple_http/src/method.cpp
    exercise_libs/simple_http/src/mime_type.cpp
    exercise_libs/simple_http/src/response.cpp
    exercise_libs/simple_http/src/disposition.cpp
    exercise_libs/simple_http/src/status_code.cpp
    INCLUDE_DIRECTORIES
    exercise_libs/simple_http/include
)

# Lecture Examples

week_executable(NAME "asio_resolver"
    SOURCES
    lecture_examples/w10_01_AsioResolver/AsioResolver.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
)

week_executable(NAME "asio_get_request"
    SOURCES
    lecture_examples/w10_02_AsioGetRequest/AsioGetRequest.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
)

week_executable(NAME "asio_sync_echo_server"
    SOURCES
    lecture_examples/w10_03_AsioSyncEchoServer/AsioSyncEchoServer.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
)

week_executable(NAME "asio_fizz_buzz_server"
    SOURCES
    lecture_examples/w10_04_AsioFizzBuzzServer/FizzBuzz.cpp
    lecture_examples/w10_04_AsioFizzBuzzServer/FizzBuzzServer.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
)

week_executable(NAME "asio_signals"
    SOURCES
    lecture_examples/w10_05_AsioSignals/AsioSignals.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
)

week_executable(NAME "multi_run"
    SOURCES
    lecture_examples/w10_06_MultiRun/MultiRun.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
)

#Exercise Templates

week_executable(NAME "julia_server"
    SOURCES
    exercise_templates/w10_template_00_JuliaServer/src/JuliaServer.cpp
    exercise_templates/w10_template_00_JuliaServer/src/bmp.cpp
    exercise_templates/w10_template_00_JuliaServer/src/image.cpp
    exercise_templates/w10_template_00_JuliaServer/src/julia.cpp
    exercise_templates/w10_template_00_JuliaServer/src/remote.cpp
    exercise_templates/w10_template_00_JuliaServer/src/server.cpp
    exercise_templates/w10_template_00_JuliaServer/src/worker_pool.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
    "w10_simple_http"
    INCLUDE_DIRECTORIES
    exercise_templates/w10_template_00_JuliaServer/include
)

week_executable(NAME "sync_julia_client"
    SOURCES
    exercise_templates/w10_template_01_SyncJuliaClient/SyncJuliaClient.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
    "w10_simple_http"
)

week_executable(NAME "async_julia_client"
    SOURCES
    exercise_templates/w10_template_02_AsyncJuliaClient/AsyncJuliaClient.cpp
    exercise_templates/w10_template_02_AsyncJuliaClient/JuliaClient.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
    "w10_simple_http"
)

# #Exercise Solutions

week_executable(NAME "solution_sync_julia_client"
    SOURCES
    exercise_solutions/w10_solution_01_SyncJuliaClient/SyncJuliaClient.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
    "w10_simple_http"
)

week_executable(NAME "solution_async_julia_client"
    SOURCES
    exercise_solutions/w10_solution_02_AsyncJuliaClient/AsyncJuliaClient.cpp
    exercise_solutions/w10_solution_02_AsyncJuliaClient/JuliaClient.cpp
    LIBRARIES
    "Threads::Threads"
    "asio"
    "w10_simple_http"
)


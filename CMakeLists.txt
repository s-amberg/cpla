cmake_minimum_required(VERSION 3.19)

project("CPlA"
    LANGUAGES CXX
)

find_package(Boost)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

include("week_lib_exe")
include(CTest)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(week01)
add_subdirectory(week02)
add_subdirectory(week03)
add_subdirectory(week04)
add_subdirectory(week05)
add_subdirectory(week06)
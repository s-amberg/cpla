cmake_minimum_required(VERSION 3.19)

#[===[ Basic Project Configuration ]===]

project("CPLA"
    LANGUAGES CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(LIBCXX_ENABLE_INCOMPLETE_FEATURES=ON)

set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

enable_testing()

#[===[ Third-party dependencies ]===]

add_subdirectory("lib")

#[===[ Per-week Subdirectories ]===]

file(GLOB CPLA_WEEKS
    RELATIVE "${PROJECT_SOURCE_DIR}"
    CONFIGURE_DEPENDS
    "week*/CMakeLists.txt"
)

# foreach(WEEK IN LISTS CPLA_WEEKS)
#     get_filename_component(WEEK "${WEEK}" DIRECTORY)
#     add_subdirectory("${WEEK}")
# endforeach()

add_subdirectory("week01")
add_subdirectory("week02")
add_subdirectory("week03")
add_subdirectory("week04")
# add_subdirectory("week05")
# add_subdirectory("week06")
# add_subdirectory("week07")
# add_subdirectory("week08")
# add_subdirectory("week09")
# add_subdirectory("week10")
# add_subdirectory("week11")
# add_subdirectory("week12")

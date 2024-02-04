add_library("CUTE" INTERFACE)
target_include_directories("CUTE" SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/CUTE")

file(GLOB_RECURSE CUTE_HEADERS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    CONFIGURE_DEPENDS
    "*.h"
)

target_sources("CUTE" INTERFACE ${CUTE_HEADERS})

add_library("cpl::cute" ALIAS "CUTE")

add_library("boost" INTERFACE)

target_include_directories("boost" SYSTEM BEFORE INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/boost")

add_library("cpl::boost" ALIAS "boost")

add_library("asio" INTERFACE)

target_include_directories("asio" SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/asio")

target_link_libraries("asio" INTERFACE
    "$<$<PLATFORM_ID:Windows>:ws2_32>"
    "$<$<PLATFORM_ID:Windows>:wsock32>"
)

add_library("cpl::asio" ALIAS "asio")

add_subdirectory("simple_http")

add_library("cpl::simple-http" ALIAS "simple-http")

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

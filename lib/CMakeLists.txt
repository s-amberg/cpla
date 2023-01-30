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
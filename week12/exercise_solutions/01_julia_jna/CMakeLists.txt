add_library("${CPL_TARGET_WEEK_PREFIX}sol01_julia_jna" SHARED
    "lib/Bmp.cpp"
    "lib/Julia.cpp"
    "lib/julia_api.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}sol01_julia_jna" PUBLIC
    "lib"
)

add_jar("${CPL_TARGET_WEEK_PREFIX}sol01_julia_jna_app"
    SOURCES
    "java/src/ch/ost/cpla/Julia.java"
    "java/src/ch/ost/cpla/JuliaJNA.java"
    INCLUDE_JARS
    "java/lib/jna-5.5.0.jar"
    ENTRY_POINT
    "ch/ost/cpla/JuliaJNA"
    OUTPUT_DIR
    "${CMAKE_BINARY_DIR}/java"
) 

add_custom_command(TARGET "${CPL_TARGET_WEEK_PREFIX}sol01_julia_jna_app" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${CPL_TARGET_WEEK_PREFIX}sol01_julia_jna> "${CMAKE_BINARY_DIR}/java"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/java/lib/jna-5.5.0.jar" "${CMAKE_BINARY_DIR}/java"
)
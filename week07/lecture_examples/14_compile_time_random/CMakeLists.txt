#[===[ LIBRARY ]===]

add_library("${CPL_TARGET_WEEK_PREFIX}14_compile_time_random_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}14_compile_time_random_lib" INTERFACE "lib")

#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}14_compile_time_random"
    "app/CompileTimeRandomDemo.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}14_compile_time_random" "${CPL_TARGET_WEEK_PREFIX}14_compile_time_random_lib")
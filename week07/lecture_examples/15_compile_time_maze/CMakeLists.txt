#[===[ LIBRARY ]===]

add_library("${CPL_TARGET_WEEK_PREFIX}15_compile_time_maze_lib" INTERFACE
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}15_compile_time_maze_lib" INTERFACE "lib")

#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}15_compile_time_maze"
    "app/CompileTimeMazeDemo.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}15_compile_time_maze" "${CPL_TARGET_WEEK_PREFIX}15_compile_time_maze_lib")
target_link_libraries("${CPL_TARGET_WEEK_PREFIX}15_compile_time_maze" "${CPL_TARGET_WEEK_PREFIX}14_compile_time_random_lib")
#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}02_move_demo"
    "MoveDemo.cpp"
)

target_compile_options("${CPL_TARGET_WEEK_PREFIX}02_move_demo" PRIVATE "-fno-elide-constructors")

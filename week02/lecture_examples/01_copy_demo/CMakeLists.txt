#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}01_copy_demo"
    "CopyDemo.cpp"
)

target_compile_options("${CPL_TARGET_WEEK_PREFIX}01_copy_demo" PRIVATE "-fno-elide-constructors")

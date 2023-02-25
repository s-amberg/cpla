#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex01_tracer"
    "TracerMain.cpp"
)

# target_compile_options("${CPL_TARGET_WEEK_PREFIX}ex01_tracer" PRIVATE
# 	"-fno-elide-constructors"
# )
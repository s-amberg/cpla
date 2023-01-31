#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}03_planets_example"
    "PlanetsExample.cpp"
)

target_compile_options("${CPL_TARGET_WEEK_PREFIX}03_planets_example" PRIVATE "-fno-elide-constructors")

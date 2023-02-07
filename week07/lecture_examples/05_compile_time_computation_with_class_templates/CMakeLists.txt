#[====[ Tests ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}05_compile_time_computation_with_class_templates"
    "CompileTimeComputationClassTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}05_compile_time_computation_with_class_templates" PRIVATE
    "cpl::cute"
)

add_test(NAME "${CPL_TARGET_WEEK_PREFIX}05_compile_time_computation_with_class_templates"
    COMMAND "${CPL_TARGET_WEEK_PREFIX}05_compile_time_computation_with_class_templates"
)

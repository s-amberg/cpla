add_library("${CPL_TARGET_WEEK_PREFIX}01_wizard"
    "lib/src/Wizard.cpp"
    "lib/src/WizardHidden.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}01_wizard" PUBLIC
    "lib/include"
)

add_executable("${CPL_TARGET_WEEK_PREFIX}01_wizard_tests"
    "tests/Test.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}01_wizard_tests" PRIVATE
    "tests"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}01_wizard_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}01_wizard"
    "cpl::cute"
)
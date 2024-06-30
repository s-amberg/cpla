add_library("${CPL_TARGET_WEEK_PREFIX}01_wizard" SHARED
    "lib/src/Wizard.cpp"
    "lib/src/WizardHidden.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}01_wizard" PUBLIC
    "lib/include"
)

add_executable("${CPL_TARGET_WEEK_PREFIX}01_wizard_tests"
    "tests/Tests.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}01_wizard_tests" PRIVATE
    "tests"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}01_wizard_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}01_wizard"
    "Catch2::Catch2WithMain"
)
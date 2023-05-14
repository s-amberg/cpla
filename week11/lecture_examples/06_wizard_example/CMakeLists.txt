add_executable("${CPL_TARGET_WEEK_PREFIX}06_wizard_example"
    "Test.cpp"
    "Wizard.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}06_wizard_example" PRIVATE
    "cpl::cute"
)
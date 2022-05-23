cmake_minimum_required(VERSION 3.19)

project(w12 LANGUAGES CXX)


# Lecture Examples

week_shared_library(NAME "wizard"
    SOURCES
    lecture_examples/w12_01_wizard_c_lib/src/Wizard.cpp
    lecture_examples/w12_01_wizard_c_lib/src/WizardHidden.cpp
    INCLUDE_DIRECTORIES
    lecture_examples/w12_01_wizard_c_lib
)

week_executable(NAME "wizard_tests"
    SOURCES
    lecture_examples/w12_01_wizard_c_lib_test/src/Test.cpp
    INCLUDE_DIRECTORIES
    lecture_examples/w12_01_wizard_c_lib_test/cute
    LIBRARIES
    w12_wizard
)

week_shared_library(NAME "cpla"
    SOURCES
    lecture_examples/w12_02_CplaLib/cpla.cpp
)

#Exercise Templates

week_shared_library(NAME "julia"
    SOURCES
    exercise_templates/w12_template_01_JuliaLib/Bmp.cpp
    exercise_templates/w12_template_01_JuliaLib/Julia.cpp
    OUTPUT_NAME
    "julia"
)

#Exercise Solutions

# To enable this, you will need to disable the "julia" library above
# week_shared_library(NAME "julia"
#     SOURCES
#     exercise_solutions/w12_solution_01_JuliaLib/Bmp.cpp
#     exercise_solutions/w12_solution_01_JuliaLib/Julia.cpp
#     exercise_solutions/w12_solution_01_JuliaLib/julia_api.cpp
#     OUTPUT_NAME
#     "julia"
# )


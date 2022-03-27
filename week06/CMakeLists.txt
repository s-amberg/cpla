cmake_minimum_required(VERSION 3.19)

project(w06 LANGUAGES CXX)

# Lecture Examples
week_executable(NAME "shape_and_square"
    SOURCES
    lecture_examples/w06_01_ShapeAndSquare/ShapeAndSquare.cpp
)

week_executable(NAME "extract_middle_1"
    SOURCES
    lecture_examples/w06_02_ExtractMiddle/ExtractMiddle.cpp
)

week_executable(NAME "extract_middle_2"
    SOURCES
    lecture_examples/w06_03_ExtractMiddle/ExtractMiddle.cpp
)

week_executable(NAME "overload_selection"
    SOURCES
    lecture_examples/w06_04_OverloadSelection/OverloadSelection.cpp
)

week_executable(NAME "substitution_error"
    SOURCES
    lecture_examples/w06_05_SubstitutionError/SubstitutionError.cpp
)

week_executable(NAME "sfinae_with_enable_if"
    SOURCES
    lecture_examples/w06_06_SFINAEwithEnableIf/SFINAEwthihEnableIf.cpp
)

week_executable(NAME "arbitrary_printer"
    SOURCES
    lecture_examples/w06_08_ArbitraryPrinter/ArbitraryPrinter.cpp
)



#Exercise Templates

week_executable(NAME "sfinae_exercise"
    SOURCES
    exercise_templates/w06_template_02_SFINAE/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_templates/w06_template_02_SFINAE/cute
)



#Exercise Solutions


week_executable(NAME "sfinae_solution"
    SOURCES
    exercise_solution/w06_solution_02_SFINAE/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_solution/w06_solution_02_SFINAE/cute
)


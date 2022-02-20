cmake_minimum_required(VERSION 3.19)

project(w01 LANGUAGES CXX)

# Lecture Examples
week_executable(NAME "stylechecker_demo"
    SOURCES
    lecture_examples/w01_lecture_00_StylecheckerDemo/src/Test.cpp
    lecture_examples/w01_lecture_00_StylecheckerDemo/src/header.cpp
	INCLUDE_DIRECTORIES
    lecture_examples/w01_lecture_00_StylecheckerDemo/cute
)
week_executable(NAME "cevelop_issues"
    SOURCES
    lecture_examples/w01_lecture_01_IssuesInCevelop/cpp17problems.cpp
)


week_executable(NAME "integral_promotion"
    SOURCES
    lecture_examples/w01_lecture_02_IntegralPromotion/integral_promotion.cpp
)

week_executable(NAME "algorithms"
    SOURCES
    lecture_examples/w01_lecture_03_Algorithms/algorithms.cpp
)

#Exercise Templates


#Exercise Solutions


week_executable(NAME "simple_tasks"
    SOURCES
    exercise_solutions/w01_solution_01_simple_tasks/src/Test.cpp
	INCLUDE_DIRECTORIES
    exercise_solutions/w01_solution_01_simple_tasks/cute
)

week_executable(NAME "fraction_type"
    SOURCES
    exercise_solutions/w01_solution_02_fraction_type/src/Test.cpp
	INCLUDE_DIRECTORIES
    exercise_solutions/w01_solution_02_fraction_type/cute
)

week_executable(NAME "dynarray"
    SOURCES
    exercise_solutions/w01_solution_03_dynarray/src/Test.cpp
	INCLUDE_DIRECTORIES
    exercise_solutions/w01_solution_03_dynarray/cute
)

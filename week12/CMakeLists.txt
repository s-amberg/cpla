set(CPL_TARGET_WEEK_PREFIX "w12_")

add_subdirectory("lecture_examples/01_wizard")

find_package("Java")

if(Java_FOUND)
    include("UseJava")
    add_subdirectory("lecture_examples/02_jna")
    add_subdirectory("exercise_templates/01_julia_jna")
    add_subdirectory("exercise_solutions/01_julia_jna")
endif()

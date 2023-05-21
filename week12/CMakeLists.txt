set(CPL_TARGET_WEEK_PREFIX "w12_")

add_subdirectory("lecture_examples/01_wizard")

find_package("Java")

if(Java_FOUND)
    include("UseJava")
    add_subdirectory("lecture_examples/02_jna")
endif()

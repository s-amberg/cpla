set(CPL_TARGET_WEEK_PREFIX "w09_")

find_package("Threads")

add_subdirectory("lecture_examples/00_non_atomic_flipper")
add_subdirectory("lecture_examples/01_atomic_flag")
add_subdirectory("lecture_examples/02_seq_cst")
add_subdirectory("lecture_examples/03_acq_rel")
add_subdirectory("lecture_examples/04_relaxed_memory_order")
add_subdirectory("lecture_examples/05_custom_types")

add_subdirectory("exercise_templates/02_student_critique")
add_subdirectory("exercise_templates/01_peterson_mutex")

add_subdirectory("exercise_solutions/02_student_critique")
add_subdirectory("exercise_solutions/01_peterson_mutex")

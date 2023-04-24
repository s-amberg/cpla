set(CPL_TARGET_WEEK_PREFIX "w08_")

add_subdirectory("lecture_examples/01_constructing_threads")
add_subdirectory("lecture_examples/02_threadable_functions")
add_subdirectory("lecture_examples/03_passing_arguments_to_threads")
add_subdirectory("lecture_examples/04_no_join_quiz")
add_subdirectory("lecture_examples/05_dangling_with_detach")
add_subdirectory("lecture_examples/06_jthread")
add_subdirectory("lecture_examples/07_knowing_your_thread")
add_subdirectory("lecture_examples/08_quiz")
add_subdirectory("lecture_examples/09_results_via_shared_state")
add_subdirectory("lecture_examples/10_results_via_promises_futures")
add_subdirectory("lecture_examples/11_std_async")
add_subdirectory("lecture_examples/12_std_async_async")


# add_subdirectory("exercise_templates/01_compile_time_hashing")
# add_subdirectory("exercise_templates/02_compile_time_fibonacci")
# add_subdirectory("exercise_templates/03_vector_literal_type")
# add_subdirectory("exercise_templates/04_temperature_type")

# add_subdirectory("exercise_solutions/02_compile_time_fibonacci")
# add_subdirectory("exercise_solutions/03_vector_literal_type")
# add_subdirectory("exercise_solutions/04_temperature_type")



# cmake_minimum_required(VERSION 3.19)

# project(w08 LANGUAGES CXX)

# find_package("Threads")

# # Lecture Examples
# week_executable(NAME "constructing_threads"
#     SOURCES
#     lecture_examples/w08_01_ConstructingThreads/ConstructingThreads.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "threadable_functions"
#     SOURCES
#     lecture_examples/w08_02_ThreadableFunctions/ThreadableFunctions.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "passing_arguments_to_threads"
#     SOURCES
#     lecture_examples/w08_03_PassingArgumentsToThreads/PassingArgumentsToThreads.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "no_join_quiz"
#     SOURCES
#     lecture_examples/w08_04_NoJoinQuiz/NoJoinQuiz.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "dangling_with_detach"
#     SOURCES
#     lecture_examples/w08_05_DanglingWithDetach/DanglingWithDetach.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "scoped_thread"
#     SOURCES
#     lecture_examples/w08_06_ScopedThread/ScopedThread.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "knowing_your_thread"
#     SOURCES
#     lecture_examples/w08_07_KnowingYourThread/KnowingYourThread.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "quiz"
#     SOURCES
#     lecture_examples/w08_08_Quiz/Quiz.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "results_via_shared_state"
#     SOURCES
#     lecture_examples/w08_09_ResultsViaSharedState/ResultsViaSharedState.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "results_via_promises_future"
#     SOURCES
#     lecture_examples/w08_10_ResultsViaPromisesFutures/ResultsViaPromisesFutures.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "std_async"
#     SOURCES
#     lecture_examples/w08_11_StdAsync/StdAsync.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "compile_time_reverse"
#     SOURCES
#     lecture_examples/w08_12_StdAsyncAsync/StdAsyncAsync.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# #Exercise Templates

# week_executable(NAME "threading_basics_01b"
#     SOURCES
#     exercise_templates/w08_template_01b_ThreadingBasics/ThreadingBasics.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# # #Exercise Solutions

# week_executable(NAME "threading_basics_01a_solution"
#     SOURCES
#     exercise_solutions/w08_solution_01a_ThreadingBasics/ThreadingBasics.cpp
#     LIBRARIES
#     "Threads::Threads"
# )

# week_executable(NAME "threading_basics_01b_solution"
#     SOURCES
#     exercise_solutions/w08_solution_01b_ThreadingBasics/ThreadingBasics.cpp
#     LIBRARIES
#     "Threads::Threads"
# )


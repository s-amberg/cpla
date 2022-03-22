cmake_minimum_required(VERSION 3.19)

project(w05 LANGUAGES CXX)

# Lecture Examples
week_executable(NAME "space_travel"
    SOURCES
    lecture_examples/w05_01_SpaceTravel/SpaceTravel.cpp
)

week_executable(NAME "int_iterator"
    SOURCES
    lecture_examples/w05_02_IntIterator/IntIterator.cpp
)

week_executable(NAME "tag_dispatching"
    SOURCES
    lecture_examples/w05_03_TagDispatching/TagDispatching.cpp
)

week_executable(NAME "boost_iterator"
    SOURCES
    lecture_examples/w05_04_BoostIterator/BoostIterator.cpp
)

week_executable(NAME "int_iterator_boost"
    SOURCES
    lecture_examples/w05_05_IntIteratorBoost/IntIteratorBoost.cpp
)

week_executable(NAME "output_iterator"
    SOURCES
    lecture_examples/w05_06_OutputIterator/OutputIterator.cpp
)

week_executable(NAME "summing_iterator"
    SOURCES
    lecture_examples/w05_07_SummingIterator/SummingIterator.cpp
)

week_executable(NAME "int_inputter"
    SOURCES
    lecture_examples/w05_08_IntInputter/IntInputter.cpp
)

week_executable(NAME "int_inputter_with_pointers"
    SOURCES
    lecture_examples/w05_09_IntInputterWithPointers/IntInputterWithPointers.cpp
)


#Exercise Templates

# week_executable(NAME "bounded_buffer_with_iterators_tests"
#     SOURCES
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/Test.cpp
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/bounded_buffer_content_suite.cpp
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/bounded_buffer_default_behavior_suite.cpp
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/bounded_buffer_heap_memory_suite.cpp
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/bounded_buffer_iterator_suite.cpp
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/bounded_buffer_non_default_constructible_element_type_suite.cpp
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/bounded_buffer_semantic_suite.cpp
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/bounded_buffer_signatures_suite.cpp
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/src/bounded_buffer_student_suite.cpp
# 	INCLUDE_DIRECTORIES
#     exercise_templates/w05_template_01_BoundedBufferWithIterators/cute
# )


week_executable(NAME "fibonacci_iterator"
    SOURCES
    exercise_templates/w05_template_03_FibonacciIterator/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_templates/w05_template_03_FibonacciIterator/cute
)



#Exercise Solutions


week_executable(NAME "lcount_with_iterator_solution"
    SOURCES
    exercise_solution/w05_solution_02_LCountWithIterator/lcount.cpp
)

week_executable(NAME "fibonacci_iterator_solution"
    SOURCES
    exercise_solution/w05_solution_03_FibonacciIterator/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_solution/w05_solution_03_FibonacciIterator/cute
)

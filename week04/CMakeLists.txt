cmake_minimum_required(VERSION 3.19)

project(w04 LANGUAGES CXX)

# Lecture Examples
week_executable(NAME "max_array_size_on_stack"
    SOURCES
    lecture_examples/w04_00_MaxArraySizeOnStack/MaxArraySizeOnStack.cpp
)

week_executable(NAME "nullptr_vs_null"
    SOURCES
    lecture_examples/w04_01_NullptrVsNull/NullptrVsNull.cpp
)

week_executable(NAME "new_examples"
    SOURCES
    lecture_examples/w04_02_NewExamples/NewExamples.cpp
)

week_executable(NAME "placement_new"
    SOURCES
    lecture_examples/w04_03_PlacementNew/PlacementNew.cpp
)

week_executable(NAME "placement_delete"
    SOURCES
    lecture_examples/w04_04_PlacementDelete/PlacementDelete.cpp
)

week_executable(NAME "non_default_constructible_point"
    SOURCES
    lecture_examples/w04_04b_NonDefaultConstructiblePoint/NonDefaultConstructiblePoint.cpp
)

week_executable(NAME "new_delete_overload"
    SOURCES
    lecture_examples/w04_05_NewDeleteOverload/src/Test.cpp
    INCLUDE_DIRECTORIES
    lecture_examples/w04_05_NewDeleteOverload/cute
)

week_executable(NAME "emplace"
    SOURCES
    lecture_examples/w04_06_Emplace/Emplace.cpp
)


#Self Study

week_executable(NAME "value_holder"
    SOURCES
    self_study/w04_01_ValueHolder/src/Test.cpp
    INCLUDE_DIRECTORIES
    self_study/w04_01_ValueHolder/cute
)

week_executable(NAME "better_value_holder"
    SOURCES
    self_study/w04_02_BetterValueHolder/src/Test.cpp
    INCLUDE_DIRECTORIES
    self_study/w04_02_BetterValueHolder/cute
)


#Exercise Templates

week_executable(NAME "not_on_heap"
    SOURCES
    exercise_templates/w04_template_01_NotOnHeap/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_templates/w04_template_01_NotOnHeap/cute
)

# week_executable(NAME "bounded_buffer_with_heap_memory_tests"
#     SOURCES
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/Test.cpp
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_content_suite.cpp
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_default_behavior_suite.cpp
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_heap_memory_suite.cpp
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_semantic_suite.cpp
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_signatures_suite.cpp
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_student_suite.cpp
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/MemoryOperationCounter.cpp
# 	INCLUDE_DIRECTORIES
#     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/cute
# )

# week_executable(NAME "bounded_buffer_for_non_default_constructible_types_tests"
#     SOURCES
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/Test.cpp
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_content_suite.cpp
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_default_behavior_suite.cpp
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_heap_memory_suite.cpp
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_non_default_constructible_element_type_suite.cpp
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_semantic_suite.cpp
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_signatures_suite.cpp
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_student_suite.cpp
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/MemoryOperationCounter.cpp
# 	INCLUDE_DIRECTORIES
#     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/cute
# )


#Exercise Solutions


week_executable(NAME "not_on_heap_solution"
    SOURCES
    exercise_solution/w04_solution_01_NotOnHeap/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_solution/w04_solution_01_NotOnHeap/cute
)

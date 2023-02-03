set(CPL_TARGET_WEEK_PREFIX "w04_")

add_subdirectory("lecture_examples/01_max_array_size_on_stack")
add_subdirectory("lecture_examples/02_nullptr_vs_null")
add_subdirectory("lecture_examples/03_new_examples")
add_subdirectory("lecture_examples/04_placement_new")
add_subdirectory("lecture_examples/05_placement_delete")
add_subdirectory("lecture_examples/06_non_default_constructible_point")
add_subdirectory("lecture_examples/07_new_delete_overload")
add_subdirectory("lecture_examples/08_emplace")

add_subdirectory("self_study/01_value_holder")
add_subdirectory("self_study/02_better_value_holder")

add_subdirectory("exercise_templates/01_not_on_heap")
add_subdirectory("exercise_templates/02_bounded_buffer_with_heap_memory")
add_subdirectory("exercise_templates/03_bounded_buffer_for_non_default_constructible_types")

add_subdirectory("exercise_solutions/01_not_on_heap")





# cmake_minimum_required(VERSION 3.19)

# project(w04 LANGUAGES CXX)

# # Lecture Examples
# week_executable(NAME "max_array_size_on_stack"
#     SOURCES
#     lecture_examples/w04_00_MaxArraySizeOnStack/MaxArraySizeOnStack.cpp
# )

# week_executable(NAME "nullptr_vs_null"
#     SOURCES
#     lecture_examples/w04_01_NullptrVsNull/NullptrVsNull.cpp
# )

# week_executable(NAME "new_examples"
#     SOURCES
#     lecture_examples/w04_02_NewExamples/NewExamples.cpp
# )

# week_executable(NAME "placement_new"
#     SOURCES
#     lecture_examples/w04_03_PlacementNew/PlacementNew.cpp
# )

# week_executable(NAME "placement_delete"
#     SOURCES
#     lecture_examples/w04_04_PlacementDelete/PlacementDelete.cpp
# )

# week_executable(NAME "non_default_constructible_point"
#     SOURCES
#     lecture_examples/w04_04b_NonDefaultConstructiblePoint/NonDefaultConstructiblePoint.cpp
# )

# week_executable(NAME "new_delete_overload"
#     SOURCES
#     lecture_examples/w04_05_NewDeleteOverload/src/Test.cpp
#     INCLUDE_DIRECTORIES
#     lecture_examples/w04_05_NewDeleteOverload/cute
# )

# week_executable(NAME "emplace"
#     SOURCES
#     lecture_examples/w04_06_Emplace/Emplace.cpp
# )


# #Self Study

# week_executable(NAME "value_holder"
#     SOURCES
#     self_study/w04_01_ValueHolder/src/Test.cpp
#     INCLUDE_DIRECTORIES
#     self_study/w04_01_ValueHolder/cute
# )

# week_executable(NAME "better_value_holder"
#     SOURCES
#     self_study/w04_02_BetterValueHolder/src/Test.cpp
#     INCLUDE_DIRECTORIES
#     self_study/w04_02_BetterValueHolder/cute
# )


# #Exercise Templates

# week_executable(NAME "not_on_heap"
#     SOURCES
#     exercise_templates/w04_template_01_NotOnHeap/src/Test.cpp
#     INCLUDE_DIRECTORIES
#     exercise_templates/w04_template_01_NotOnHeap/cute
# )

# # week_executable(NAME "bounded_buffer_with_heap_memory_tests"
# #     SOURCES
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/Test.cpp
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_content_suite.cpp
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_default_behavior_suite.cpp
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_heap_memory_suite.cpp
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_semantic_suite.cpp
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_signatures_suite.cpp
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/bounded_buffer_student_suite.cpp
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/src/MemoryOperationCounter.cpp
# # 	INCLUDE_DIRECTORIES
# #     exercise_templates/w04_template_02_BoundedBufferWithHeapMemory/cute
# # )

# # week_executable(NAME "bounded_buffer_for_non_default_constructible_types_tests"
# #     SOURCES
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/Test.cpp
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_content_suite.cpp
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_default_behavior_suite.cpp
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_heap_memory_suite.cpp
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_non_default_constructible_element_type_suite.cpp
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_semantic_suite.cpp
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_signatures_suite.cpp
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/bounded_buffer_student_suite.cpp
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/src/MemoryOperationCounter.cpp
# # 	INCLUDE_DIRECTORIES
# #     exercise_templates/w04_template_03_BoundedBufferForNonDefaultConstructibleTypes/cute
# # )


# #Exercise Solutions


# week_executable(NAME "not_on_heap_solution"
#     SOURCES
#     exercise_solution/w04_solution_01_NotOnHeap/src/Test.cpp
#     INCLUDE_DIRECTORIES
#     exercise_solution/w04_solution_01_NotOnHeap/cute
# )

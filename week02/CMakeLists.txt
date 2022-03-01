cmake_minimum_required(VERSION 3.19)

project(w02 LANGUAGES CXX)

# Lecture Examples
week_executable(NAME "copy_demo"
    SOURCES
    lecture_examples/w02_lecture_00_CopyDemo/CopyDemo.cpp
)
set_target_properties(w02_copy_demo PROPERTIES CXX_STANDARD 17)
target_compile_options(w02_copy_demo PRIVATE "-fno-elide-constructors")

week_executable(NAME "move_demo"
    SOURCES
    lecture_examples/w02_lecture_01_MoveDemo/MoveDemo.cpp
)
set_target_properties(w02_move_demo PROPERTIES CXX_STANDARD 17)
target_compile_options(w02_move_demo PRIVATE "-fno-elide-constructors")

week_executable(NAME "planets_example"
    SOURCES
    lecture_examples/w02_lecture_02_PlanetsExample/main.cpp
)

week_executable(NAME "temporary_materialization"
    SOURCES
    lecture_examples/w02_lecture_03_TemporaryMaterialization/TemporaryMaterialization.cpp
)

week_executable(NAME "overload_resolution"
    SOURCES
    lecture_examples/w02_lecture_04_OverloadResolution/OverloadResolution.cpp
)

week_executable(NAME "overload_resolution_member_functions"
    SOURCES
    lecture_examples/w02_lecture_05_OverloadResolutionMemberFunctions/OverloadResolutionMemberFunctions.cpp
)

week_executable(NAME "copy_and_move_constructors"
    SOURCES
    lecture_examples/w02_lecture_06_CopyAndMoveConstructors/CopyAndMoveConstructors.cpp
)

week_executable(NAME "copy_and_move_assignment"
    SOURCES
    lecture_examples/w02_lecture_07_CopyAndMoveAssignment/CopyAndMoveAssignment.cpp
)

week_executable(NAME "mandatory_elision"
    SOURCES
    lecture_examples/w02_lecture_08_MandatoryElision/MandatoryElision.cpp
)

week_executable(NAME "copy_elision"
    SOURCES
    lecture_examples/w02_lecture_09_CopyElision/CopyElision.cpp
)

week_executable(NAME "copy_elision_exceptions"
    SOURCES
    lecture_examples/w02_lecture_10_CopyElisionExceptions/CopyElisionExceptions.cpp
)

week_executable(NAME "copy_elision_and_std_move"
    SOURCES
    lecture_examples/w02_lecture_11_CopyElisionAndStdMove/CopyElisionAndStdMove.cpp
)

week_executable(NAME "lifetime_extension"
    SOURCES
    lecture_examples/w02_lecture_12_LifetimeExtension/LifetimeExtension.cpp
)


#Exercise Templates

week_executable(NAME "tracer"
    SOURCES
    exercise_templates/w02_template_01_Tracer/Main.cpp
)

week_executable(NAME "bounded_buffer_tests"
    SOURCES
    exercise_templates/w02_template_02_BoundedBuffer/src/Test.cpp
    exercise_templates/w02_template_02_BoundedBuffer/src/bounded_buffer_content_suite.cpp
    exercise_templates/w02_template_02_BoundedBuffer/src/bounded_buffer_default_behavior_suite.cpp
    exercise_templates/w02_template_02_BoundedBuffer/src/bounded_buffer_semantic_suite.cpp
    exercise_templates/w02_template_02_BoundedBuffer/src/bounded_buffer_signatures_suite.cpp
    exercise_templates/w02_template_02_BoundedBuffer/src/bounded_buffer_student_suite.cpp
    exercise_templates/w02_template_02_BoundedBuffer/src/MemoryOperationCounter.cpp
	INCLUDE_DIRECTORIES
    exercise_templates/w02_template_02_BoundedBuffer/cute
)


#Exercise Solutions




cmake_minimum_required(VERSION 3.19)

project(w03 LANGUAGES CXX)

# Lecture Examples
week_executable(NAME "big_object_container"
    SOURCES
    lecture_examples/w03_lecture_01_BigObjectContainer/BigObjectContainer.cpp
)

week_executable(NAME "initialize_list_as_template_argument"
    SOURCES
    lecture_examples/w03_lecture_02_InitializerListAsTemplateArgument/InitializerListAsTemplateArgument.cpp
)

week_executable(NAME "auto_return_type"
    SOURCES
    lecture_examples/w03_lecture_03_AutoReturnType/AutoReturnType.cpp
)

week_executable(NAME "do_something_by_value"
    SOURCES
    lecture_examples/w03_lecture_04_DoSomethingByValue/DoSomethingByValue.cpp
)

week_executable(NAME "do_something_by_ref"
    SOURCES
    lecture_examples/w03_lecture_05_DoSomethingByRef/DoSomethingByRef.cpp
)

week_executable(NAME "do_something_by_const_ref"
    SOURCES
    lecture_examples/w03_lecture_06_DoSomethingByConstRef/DoSomethingByConstRef.cpp
)

week_executable(NAME "do_something_by_fwd_ref"
    SOURCES
    lecture_examples/w03_lecture_07_DoSomethingByFwdRef/DoSomethingByFwdRef.cpp
)

week_executable(NAME "do_something_by_perfect_forwarding"
    SOURCES
    lecture_examples/w03_lecture_08_DoSomethingByPerfectForwarding/DoSomethingByPerfectForwarding.cpp
)

week_executable(NAME "fun_with_lambdas"
    SOURCES
    lecture_examples/w03_lecture_09_FunWithLambdas/FunWithLambdas.cpp
)


#Exercise Templates

week_executable(NAME "type_trivia"
    SOURCES
    exercise_templates/w03_template_02_TypeTrivia/Application.cpp
    exercise_templates/w03_template_02_TypeTrivia/Question.cpp
    exercise_templates/w03_template_02_TypeTrivia/QuestionGenerator.cpp
    exercise_templates/w03_template_02_TypeTrivia/Trivia.cpp
)

# week_executable(NAME "bounded_buffer_with_factory_function_tests"
#     SOURCES
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/src/Test.cpp
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/src/bounded_buffer_content_suite.cpp
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/src/bounded_buffer_default_behavior_suite.cpp
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/src/bounded_buffer_make_buffer_suite.cpp
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/src/bounded_buffer_semantic_suite.cpp
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/src/bounded_buffer_signatures_suite.cpp
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/src/bounded_buffer_student_suite.cpp
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/src/MemoryOperationCounter.cpp
# 	INCLUDE_DIRECTORIES
#     exercise_templates/w03_template_03_BoundedBufferWithFactoryFunction/cute
# )


#Exercise Solutions




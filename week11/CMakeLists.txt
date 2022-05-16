cmake_minimum_required(VERSION 3.19)

project(w11 LANGUAGES CXX)


# Lecture Examples

week_executable(NAME "noexcept_keyword"
    SOURCES
    lecture_examples/w11_01_noexceptKeyword/noexceptKeyword.cpp
)

week_executable(NAME "explosive_liquids"
    SOURCES
    lecture_examples/w11_02_ExplosiveLiquids/ExplosiveLiquids.cpp
)

week_executable(NAME "noexcept_box"
    SOURCES
    lecture_examples/w11_03_NoexceptBox/NoexceptBox.cpp
)

week_executable(NAME "terminate"
    SOURCES
    lecture_examples/w11_04_Terminate/Terminate.cpp
)

week_executable(NAME "void_ptr_in_c"
    SOURCES
    lecture_examples/w11_05_VoidPtrInC/VoidPtrInC.cpp
)

week_executable(NAME "wizard_example"
    SOURCES
    lecture_examples/w11_06_WizardExample/Wizard.cpp
    lecture_examples/w11_06_WizardExampleTest/src/Test.cpp
    INCLUDE_DIRECTORIES
    lecture_examples/w11_06_WizardExample
    lecture_examples/w11_06_WizardExampleTest/cute
)

week_executable(NAME "wizard_pimpl_with_shared_ptr"
    SOURCES
    lecture_examples/w11_07_WizardWithSharedPtr/WizardPimpl.cpp
    lecture_examples/w11_07_WizardWithSharedPtr/main.cpp
)

week_executable(NAME "wizard_pimpl_with_unique_ptr"
    SOURCES
    lecture_examples/w11_08_WizardWithUniquePtr/WizardPimpl.cpp
    lecture_examples/w11_08_WizardWithUniquePtr/main.cpp
)

#Exercise Templates

week_executable(NAME "pimpl_unicorn"
    SOURCES
    exercise_templates/w11_template_02_PimplUnicorn/Unicorn.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/TestMoveAssignUnicorn.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/TestMoveConstructUnicorn.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/Test.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/CreateFreddy.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/TestUnicornFly.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/TestCopyAssignUnicorn.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/TestUnicornGlitter.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/TestCopyConstructUnicorn.cpp
    exercise_templates/w11_template_02_PimplUnicorn/tests/TestCreateUnicorn.cpp
    INCLUDE_DIRECTORIES
    exercise_templates/w11_template_02_PimplUnicorn/cute
    exercise_templates/w11_template_02_PimplUnicorn
)

#Exercise Solutions

week_executable(NAME "pimpl_unicorn_solution"
    SOURCES
    exercise_solution/w11_solution_02_PimplUnicorn/Unicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/TestMoveAssignUnicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/TestMoveConstructUnicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/Test.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/CreateFreddy.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/TestUnicornFly.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/TestCopyAssignUnicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/TestUnicornGlitter.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/TestCopyConstructUnicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicorn/tests/TestCreateUnicorn.cpp
    INCLUDE_DIRECTORIES
    exercise_solution/w11_solution_02_PimplUnicorn/cute
    exercise_solution/w11_solution_02_PimplUnicorn
)

week_executable(NAME "pimpl_unicorn_with_pimpl_ptr_solution"
    SOURCES
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/Unicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/TestMoveAssignUnicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/TestMoveConstructUnicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/Test.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/CreateFreddy.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/TestUnicornFly.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/TestCopyAssignUnicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/TestUnicornGlitter.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/TestCopyConstructUnicorn.cpp
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/tests/TestCreateUnicorn.cpp
    INCLUDE_DIRECTORIES
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr/cute
    exercise_solution/w11_solution_02_PimplUnicornWithPimplPtr
)


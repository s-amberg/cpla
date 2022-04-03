cmake_minimum_required(VERSION 3.19)

project(w07 LANGUAGES CXX)

# Lecture Examples
week_executable(NAME "compile_time_function"
    SOURCES
    lecture_examples/w07_lecture_01_CompileTimeFunction/CompileTimeFunction.cpp
)

week_executable(NAME "compile_time_undefined_behavior"
    SOURCES
    lecture_examples/w07_lecture_02_CompileTimeUndefinedBehavior/CTUB.cpp
)

week_executable(NAME "compile_time_invalid_branch"
    SOURCES
    lecture_examples/w07_lecture_03_CompileTimeInvalidBranch/InvalidBranch.cpp
)

week_executable(NAME "compile_time_literal_type_example"
    SOURCES
    lecture_examples/w07_lecture_04_LiteralTypeExample/Vector.cpp
)

week_executable(NAME "compile_time_computation_with_class_template"
    SOURCES
    lecture_examples/w07_lecture_05_CompileTimeComputationWithClassTemplates/src/Test.cpp
    INCLUDE_DIRECTORIES
    lecture_examples/w07_lecture_05_CompileTimeComputationWithClassTemplates/cute
)

week_executable(NAME "speed_value_with_factory_functions"
    SOURCES
    lecture_examples/w07_lecture_06_SpeedValueWithFactoryFunctions/src/Test.cpp
    lecture_examples/w07_lecture_06_SpeedValueWithFactoryFunctions/src/Speed.cpp
    INCLUDE_DIRECTORIES
    lecture_examples/w07_lecture_06_SpeedValueWithFactoryFunctions/cute
)

week_executable(NAME "speed_value_with_tags"
    SOURCES
    lecture_examples/w07_lecture_07_SpeedValueWithTags/src/Test.cpp
    INCLUDE_DIRECTORIES
    lecture_examples/w07_lecture_07_SpeedValueWithTags/cute
)

week_executable(NAME "speed_udl"
    SOURCES
    lecture_examples/w07_lecture_08_SpeedUDL/src/Test.cpp
    INCLUDE_DIRECTORIES
    lecture_examples/w07_lecture_08_SpeedUDL/cute
)

week_executable(NAME "string_udl"
    SOURCES
    lecture_examples/w07_lecture_09_StringUDL/stringUDL.cpp
)

week_executable(NAME "raw_udl"
    SOURCES
    lecture_examples/w07_lecture_10_RawUDLRuntime/RawUDL.cpp
)

week_executable(NAME "compile_time_ternary"
    SOURCES
    lecture_examples/w07_lecture_11_CompileTimeTernary/CompileTimeTernary.cpp
)

week_executable(NAME "compile_time_reverse"
    SOURCES
    lecture_examples/w07_lecture_12_CompileTimeReverse/CompileTimeReverse.cpp
)

week_executable(NAME "arbitrary_printer_reiterated"
    SOURCES
    lecture_examples/w07_lecture_13_ArbitraryPrinterReiterated/ArbitraryPrinter.cpp
)


#Exercise Templates

week_executable(NAME "runtime_hashing"
    SOURCES
    exercise_templates/w07_template_01_CompileTimeHashing/runtime.cpp
)

week_executable(NAME "compile_time_hashing"
    SOURCES
    exercise_templates/w07_template_01_CompileTimeHashing/compile_time.cpp
)

week_executable(NAME "compile_time_fibonacci"
    SOURCES
    exercise_templates/w07_template_02_CompileTimeFibonacci/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_templates/w07_template_02_CompileTimeFibonacci/cute
)

week_executable(NAME "vector_literal_type"
    SOURCES
    exercise_templates/w07_template_03_VectorLiteralType/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_templates/w07_template_03_VectorLiteralType/cute
)

week_executable(NAME "temperature_type"
    SOURCES
    exercise_templates/w07_template_04_TemperatureType/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_templates/w07_template_04_TemperatureType/cute
)


#Exercise Solutions


week_executable(NAME "compile_time_fibonacci_solution"
    SOURCES
    exercise_solution/w07_solution_02_CompileTimeFibonacci/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_solution/w07_solution_02_CompileTimeFibonacci/cute
)

#for gcc
#target_compile_options(w07_compile_time_fibonacci_solution PRIVATE "-fconstexpr-ops-limit=100000000000000")
#target_compile_options(w07_compile_time_fibonacci_solution PRIVATE "-fconstexpr-cache-depth=50")

#for clang
#target_compile_options(w07_compile_time_fibonacci_solution PRIVATE "-fconstexpr-steps=4000000000")

week_executable(NAME "vector_literal_type_solution"
    SOURCES
    exercise_solution/w07_solution_03_VectorLiteralType/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_solution/w07_solution_03_VectorLiteralType/cute
)

week_executable(NAME "temperature_type_solution"
    SOURCES
    exercise_solution/w07_solution_04_TemperatureType/src/Test.cpp
    INCLUDE_DIRECTORIES
    exercise_solution/w07_solution_04_TemperatureType/cute
)

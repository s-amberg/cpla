add_library("simple-http" STATIC
    "src/disposition.cpp"
    "src/header.cpp"
    "src/message.cpp"
    "src/method.cpp"
    "src/mime_type.cpp"
    "src/request.cpp"
    "src/response.cpp"
    "src/status_code.cpp"
)

target_compile_features("simple-http" PUBLIC
    "cxx_std_20"
)

target_compile_options("simple-http" PRIVATE
    "$<$<CXX_COMPILER_ID:Clang,GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:Clang,GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:Clang,GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:Clang,GNU>:-pedantic-errors>"
)

target_include_directories("simple-http" SYSTEM PUBLIC
    "include"
)

set_target_properties("simple-http" PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED YES
)

add_executable("simple-http-tests"
    "tests/src/message_suite.cpp"
    "tests/src/mime_type_suite.cpp"
    "tests/src/Test.cpp"
)

target_link_libraries("simple-http-tests" PRIVATE
    "simple-http"
    "cpl::cute"
)

add_test(NAME "simple-http-tests" COMMAND "simple-http-tests")

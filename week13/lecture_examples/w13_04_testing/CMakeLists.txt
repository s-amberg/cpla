cmake_minimum_required(VERSION "3.12.0")

project("answer" LANGUAGES CXX)

enable_testing()

add_library("${PROJECT_NAME}"
  "answer.cpp"
)

add_executable("test_runner"
  "Test.cpp"
)

target_link_libraries("test_runner" PRIVATE "answer")

target_include_directories("test_runner" SYSTEM PRIVATE "cute")

add_test("tests" "test_runner")
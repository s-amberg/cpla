project(answer LANGUAGES CXX)

enable_testing()

include_directories(cute)

add_library(answer answer.cpp)
add_executable(test_runner Test.cpp)
target_link_libraries(test_runner answer)

add_test(tests test_runner)
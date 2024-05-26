cmake_minimum_required(VERSION "3.12.0")

project("my_lib"
  LANGUAGES CXX
)

add_library("my_lib"
  "lib.cpp"
)

target_compile_features("my_lib" PUBLIC
  "cxx_std_20"
)

set_target_properties("my_lib" PROPERTIES
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)
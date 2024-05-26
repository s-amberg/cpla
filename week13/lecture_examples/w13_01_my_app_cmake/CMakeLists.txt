cmake_minimum_required(VERSION "3.12.0")

project("my_app"
  LANGUAGES CXX
)

add_executable("my_app"
  "main.cpp"
)

target_compile_features("my_app" PUBLIC
  "cxx_std_20"
)

set_target_properties("my_app" PROPERTIES
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)
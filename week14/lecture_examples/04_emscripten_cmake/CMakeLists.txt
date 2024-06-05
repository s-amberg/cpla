cmake_minimum_required(VERSION 3.19)

project("emscripten_cmake" LANGUAGES CXX)

add_library("w14_04_emscripten_cmake_lib"
  "src/lib.cpp"
)

target_include_directories("w14_04_emscripten_cmake_lib" PUBLIC
  "include"
)

add_executable("w14_04_emscripten_cmake"
  "src/main.cpp"
)

target_link_libraries("w14_04_emscripten_cmake"
  "w14_04_emscripten_cmake_lib"
)

#!/usr/bin/env bash

mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE="Debug" -DBUILD_SHARED_LIBS=False -DSFML_USE_STATIC_STD_LIBS=True && cmake --build .


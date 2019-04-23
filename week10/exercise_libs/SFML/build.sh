#!/usr/bin/env bash

mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE="Debug" -DBUILD_SHARED_LIBS=False && make


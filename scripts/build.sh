#!/usr/bin/env sh

BUILD_TYPE=Debug

if [ "$1" == "release" ]; then
    BUILD_TYPE=Release
fi

cmake -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
cmake --build build

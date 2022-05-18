#!/usr/bin/env sh

BUILD_TYPE=Debug

if [ "$1" == "release" ]; then
    BUILD_TYPE=Release
fi

if grep -rnw 'CMakeLists.txt' -e '__raylib-template__'; then
    printf '\n\n=================================================\n'
    printf "Configuring project, this only happens once\n"
    read -p 'Enter project name (no whitespace): ' PROJECT_NAME
    ./scripts/setup.sh ${PROJECT_NAME}
    printf '\n=================================================\n\n'
fi

cmake -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
cmake --build build

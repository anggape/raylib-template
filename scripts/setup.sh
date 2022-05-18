#!/usr/bin/env sh

if [ -z "$1" ]; then
    echo "invalid project name"
    exit 1
fi

function ___setup_name() {
    sed -i "s/__raylib-template__/${1}/g" ${2}
}

___setup_name ${1} CMakeLists.txt
___setup_name ${1} src/main.c
___setup_name ${1} .vscode/launch.json

cmake_minimum_required(VERSION 3.13)
project(raylib-template
    LANGUAGES C CXX
    VERSION 1.0.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty/raylib)

add_executable(${PROJECT_NAME}
    src/main.c
)
target_link_libraries(${PROJECT_NAME}
    raylib
)

cmake_minimum_required(VERSION 3.13)
project(__raylib-template__
    LANGUAGES C CXX
    VERSION 1.0.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)
CPMGH(raysan5/raylib 5ecc289)

add_executable(${PROJECT_NAME}
    src/main.c
)
target_link_libraries(${PROJECT_NAME}
    raylib
)
target_include_directories(${PROJECT_NAME} PUBLIC
    include
)

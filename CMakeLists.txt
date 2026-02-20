cmake_minimum_required(VERSION 3.16)

project(minesweeper)

add_executable(${PROJECT_NAME} src/main.cpp src/game.cpp src/elements.cpp src/utilities.cpp)

add_subdirectory(dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif
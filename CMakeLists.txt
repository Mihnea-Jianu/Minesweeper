cmake_minimum_required(VERSION 3.28)

project(minesweeper)

add_executable(${PROJECT_NAME} src/main.cpp src/game.cpp src/elements.cpp src/utilities.cpp)

# Below, we are adding GLFW as a subdirectory so CMake knows to compile it before trying
# to compile our code. This also adds GLFW's include and library paths to our compiler's
# include and library paths. So all that is left to do is to link the library.

add_subdirectory(dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Below, CMake is trying to make sure we can find the OpenGL library that ships with the
# operating system (usually OpenGL 1.2). Once we are sure it exists, we link against it.

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# MSVC used to complain about the use of functions from the cstring API.
# The if statement below tells MSVC to ignore that.

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
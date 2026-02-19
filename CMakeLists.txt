cmake_minimum_required(VERSION 3.16...3.28)

project(MINESWEEPER)

add_executable(${PROJECT_NAME} src/main.cpp src/game.cpp src/elements.cpp src/utilities.cpp)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/build/src)
target_link_libraries(${PROJECT_NAME} glfw3)
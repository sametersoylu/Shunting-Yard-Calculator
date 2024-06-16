cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "Calculator")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} source/main.cpp)
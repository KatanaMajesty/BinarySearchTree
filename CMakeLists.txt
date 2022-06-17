cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(BinarySearchTree VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SRC ./src/*.cpp)
set(INC ./include/)

add_executable(${PROJECT_NAME} ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME} PUBLIC ${INC})
cmake_minimum_required(VERSION 3.1)

project(ancud_test_task)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_EXE ./src/source.cpp)

add_executable(main ${SOURCE_EXE})
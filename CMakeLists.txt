cmake_minimum_required(VERSION 3.16)
project(lab4 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(task1 task1/main.cc task1/money.cc)
add_executable(task2 task2/main.cc task2/money.cc)
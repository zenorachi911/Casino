cmake_minimum_required(VERSION 3.10)
project(Casino)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCE casinoproject.cpp)

add_executable(Casino ${SOURCE})
cmake_minimum_required(VERSION 3.6)
project(pipe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp testpipe.cpp testSignal.cpp)
add_executable(pipe ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.16)
project(loggerCpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_subdirectory(source)
add_subdirectory(test)

cmake_minimum_required(VERSION 2.8.12.2)
project(Project2)

set(CMAKE_CSS_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Passenger.cpp Passenger.h Event.cpp Event.h)
add_executable(project2 ${SOURCE_FILES})
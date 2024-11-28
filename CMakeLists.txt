cmake_minimum_required(VERSION 3.30.5)

set(This laborw10_3)

project(${This} C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers 
    labor10_3.hpp
)
set(Sources 
    labor10_3.cpp
)


add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)

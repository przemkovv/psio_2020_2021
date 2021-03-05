cmake_minimum_required(VERSION 3.5)

project(Lab01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab01 main.cpp)
set_target_properties(Lab01 PROPERTIES
    CXX_EXTENSIONS OFF
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

cmake_minimum_required(VERSION 3.5)

project(PSiO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab01 Lab01/main.cpp)
add_executable(Lab02 Lab02/main.cpp)
add_executable(Lab03 Lab03/main.cpp)
set_target_properties(Lab01 Lab02 Lab03
    PROPERTIES
    CXX_EXTENSIONS OFF
)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
endif()

cmake_minimum_required(VERSION 3.10)
project(task_8)

set(CMAKE_CXX_STANDARD 11)

add_executable(task_8 main.cpp headers/functions.h
        headers/Unit.h sourseFiles/Unit.cpp
        headers/Animal.h sourseFiles/Animal.cpp
        headers/Bear.h sourseFiles/Bear.cpp
        headers/Pig.h sourseFiles/Pig.cpp
        headers/Man.h sourseFiles/Man.cpp
        headers/ManBearPig.h sourseFiles/ManBearPig.cpp)
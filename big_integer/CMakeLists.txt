cmake_minimum_required(VERSION 3.10)
project(big_integer)

set(CMAKE_CXX_STANDARD 11)

add_executable(big_integer_testing big_integer.cpp big_integer.h my_vector_impl.cpp my_vector.h
        big_integer_testing.cpp gtest/gtest_main.cc gtest/gtest-all.cc gtest/gtest.h)
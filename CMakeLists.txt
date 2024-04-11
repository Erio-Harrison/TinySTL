cmake_minimum_required(VERSION 3.27)
project(TinySTL)

set(CMAKE_CXX_STANDARD 20)

add_executable(TinySTL main.cpp
        DataStructures
        Algorithms
        Test
        Functors)

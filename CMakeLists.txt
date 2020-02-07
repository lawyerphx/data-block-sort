cmake_minimum_required(VERSION 3.15)
project(sort)

set(CMAKE_CXX_STANDARD 14)

add_executable(sort main.cpp data_structures/data_block.h data_structures/area.h algorithms/qsort_solve.h)
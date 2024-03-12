cmake_minimum_required(VERSION 3.26)
project(DataStructureExperiments)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# common headers
include_directories(common)

# exp1 executables
add_executable(exp1task1 exp1/task1/main.cpp)
add_executable(exp1task2 exp1/task2/main.cpp)
add_executable(exp1task3 exp1/task3/main.cpp
        exp1/task3/SeqJosephusCircle.h
        exp1/task3/SeqJosephusCircle.cpp
        exp1/task3/LinkedJosephusCircle.cpp
        exp1/task3/LinkedJosephusCircle.h)

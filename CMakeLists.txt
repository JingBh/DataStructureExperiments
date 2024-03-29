cmake_minimum_required(VERSION 3.26)
project(DataStructureExperiments)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# common headers
include_directories(common)

# exp1 executables
# add_executable(exp1task1 exp1/task1/main.cpp)
# add_executable(exp1task2 exp1/task2/main.cpp)
# add_executable(exp1task3 exp1/task3/main.cpp
#         exp1/task3/SeqJosephusCircle.h
#         exp1/task3/SeqJosephusCircle.cpp
#         exp1/task3/LinkedJosephusCircle.cpp
#         exp1/task3/LinkedJosephusCircle.h)
# add_executable(exp1task4 exp1/task4/main.cpp)

# exp2 executables
add_executable(exp2task1 exp2/task1/main.cpp)
add_executable(exp2task2 exp2/task2/main.cpp)
add_executable(exp2task3 exp2/task3/main.cpp
        exp2/task3/LinkedCircularQueue.h)
add_executable(exp2task4 exp2/task4/main.cpp)
add_executable(exp2task5 exp2/task5/main.cpp
        exp2/task5/SuffixExpression.cpp
        exp2/task5/SuffixExpression.h)

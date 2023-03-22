cmake_minimum_required(VERSION 3.24)
project(TC_Proiect_1_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(TC_Proiect_1_4 main.cpp StackParser.cpp StackParser.h Transition.cpp Transition.h auxiliary.h ParseState.cpp ParseState.h)

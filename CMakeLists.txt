cmake_minimum_required(VERSION 3.17)
project(TP4___modelisation)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP4___modelisation main.cpp)
target_link_libraries(TP4___modelisation -lopenGL32 -lfreeGLUT)
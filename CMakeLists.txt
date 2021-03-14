cmake_minimum_required(VERSION 3.17)
project(TPSurface_parametriques)

set(CMAKE_CXX_STANDARD 14)

add_executable(TPSurface_parametriques main_surfaces_parametriques.cpp)
target_link_libraries(TPSurface_parametriques -lopenGL32 -lfreeGLUT)
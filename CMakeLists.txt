cmake_minimum_required(VERSION 3.21)
project(DiningPhilosophers)

set(CMAKE_CXX_STANDARD 20)

add_executable(Naive naive.cpp)
add_executable(Starve starve.cpp)
add_executable(Asymmetric asymmetric.cpp)


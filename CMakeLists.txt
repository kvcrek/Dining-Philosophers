cmake_minimum_required(VERSION 3.21)
project(DiningPhilosophers)

set(CMAKE_CXX_STANDARD 20)


file(GLOB sources src/*.cpp)

add_executable(main ${sources})

target_include_directories(main
        PRIVATE
        include/)


cmake_minimum_required(VERSION 3.21)
project(DiningPhilosophers)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES src/main.cpp
        src/arbiter.cpp
        src/asymmetric.cpp
        src/cout_lock.cpp
        src/fork.cpp
        src/main.cpp
        src/naive.cpp
        src/philosopher.cpp
        src/starve.cpp
        src/stopwatch.cpp)

add_executable(main ${SOURCE_FILES})

target_include_directories(main
        PRIVATE
        include/)


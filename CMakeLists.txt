cmake_minimum_required(VERSION 3.21)
project(DiningPhilosophers)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES src/main.cpp
        src/arbiter.cpp
        src/asymmetric.cpp
        src/cout_lock.cpp
        src/fork.cpp
        src/naive.cpp
        src/philosopher.cpp
        src/starve.cpp
        src/stopwatch.cpp)

add_executable(main ${SOURCE_FILES})
target_include_directories(main
        PRIVATE
        include/)

add_executable(bench
        benchmark/allocation_bench.cpp
        src/philosopher.cpp
        src/fork.cpp
        src/arbiter.cpp
        src/asymmetric.cpp
        src/cout_lock.cpp
        src/naive.cpp
        src/starve.cpp
        src/stopwatch.cpp)

target_include_directories(bench
        PRIVATE
        include/)

target_link_libraries(bench benchmark::benchmark)
find_package(benchmark REQUIRED)
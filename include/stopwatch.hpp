#pragma once

#include <chrono>
#include <iostream>

class Stopwatch {
public:
    Stopwatch();

    bool start();

    bool stop();

    std::chrono::duration<double,std::milli> getAverageTime() const;

    std::chrono::duration<double,std::milli> getTotalElapsedTime() const;

    size_t getLapAmount() const;

private:
    bool flag;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, stopTime;
    std::chrono::duration<double,std::milli> totalElapsedTime;
    size_t laps;
};
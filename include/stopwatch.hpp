#pragma once

#include <chrono>
#include <iostream>

class Stopwatch {
public:
    Stopwatch();

    void start();

    void stop();

    //Returns average time in milliseconds
    double getAverageTime();

    //Returns total elapsed time in milliseconds
    double getTotalElapsedTime();

    int getLapAmount();

private:
    bool flag;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, stopTime;
    double totalElapsedTime;
    int laps;
};
#include "stopwatch.hpp"

Stopwatch::Stopwatch() {
    flag = false;
    totalElapsedTime = 0;
    laps = 0;
}

void Stopwatch::start() {
    if (!flag) {
        flag = true;
    } else {
        std::cout << "Stopwatch is already started" << std::endl;
        return;
    }
    startTime = std::chrono::high_resolution_clock::now();
}

void Stopwatch::stop() {
    if (flag) {
        flag = false;
    } else {
        std::cout << "Stopwatch is already stopped" << std::endl;
        return;
    }
    stopTime = std::chrono::high_resolution_clock::now();
    totalElapsedTime += std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count();
    laps++;
}

double Stopwatch::getAverageTime() {
    return (totalElapsedTime / laps) / 1000;
}

double Stopwatch::getTotalElapsedTime() {
    return totalElapsedTime / 1000;
}

int Stopwatch::getLapAmount() {
    return laps;
}
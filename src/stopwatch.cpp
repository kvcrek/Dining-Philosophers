#include "stopwatch.hpp"

Stopwatch::Stopwatch() :
        flag{false},
        totalElapsedTime{0},
        laps{0} {}

bool Stopwatch::start() {
    if (!flag) {
        flag = true;
    } else {
        return false;
    }
    startTime = std::chrono::high_resolution_clock::now();
    return true;
}

bool Stopwatch::stop() {
    if (flag) {
        flag = false;
    } else {
        return false;
    }
    stopTime = std::chrono::high_resolution_clock::now();
    totalElapsedTime += (stopTime - startTime);
    laps++;
    return true;
}

std::chrono::duration<double, std::milli> Stopwatch::getAverageTime() const {
    return (totalElapsedTime / laps);
}

std::chrono::duration<double, std::milli> Stopwatch::getTotalElapsedTime() const {
    return totalElapsedTime;
}

size_t Stopwatch::getLapAmount() const {
    return laps;
}
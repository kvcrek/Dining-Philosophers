#include "stopwatch.hpp"

Stopwatch::Stopwatch() :
        flag{false},
        totalElapsedTime{0},
        laps{0} {}

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
    totalElapsedTime += (stopTime - startTime);
    laps++;
}

std::chrono::duration<double,std::milli> Stopwatch::getAverageTime() const {
    return (totalElapsedTime / laps);
}

std::chrono::duration<double,std::milli> Stopwatch::getTotalElapsedTime() const {
    return totalElapsedTime;
}

size_t Stopwatch::getLapAmount() const {
    return laps;
}
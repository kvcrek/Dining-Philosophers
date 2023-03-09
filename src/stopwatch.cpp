#include "stopwatch.hpp"

Stopwatch::Stopwatch() :
        flag{false},
        totalElapsedTime{0},
        laps{0} {}

void Stopwatch::start() {
    try {
        if (!flag) {
            flag = true;
        } else {
            throw std::runtime_error("Stopwatch is already started");
        }
        startTime = std::chrono::high_resolution_clock::now();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void Stopwatch::stop() {
    try {
        if (flag) {
            flag = false;
        } else {
            throw std::runtime_error("Stopwatch is already stopped");
        }
        stopTime = std::chrono::high_resolution_clock::now();
        totalElapsedTime += (stopTime - startTime);
        laps++;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
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
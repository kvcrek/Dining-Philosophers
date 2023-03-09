#include "philosopher.hpp"

bool Philosopher::statusMessageEnabled = true;

Philosopher::Philosopher(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right)
        : id(id),
          leftFork(std::move(left)),
          rightFork(std::move(right)),
          meals{},
          paused{true},
          thr{std::thread(&Philosopher::run, this)} {
}

void Philosopher::start() {
    paused = false;
}

void Philosopher::stop() {
    paused = true;
}

void Philosopher::enableStatusMessages() {
    statusMessageEnabled = true;
}

void Philosopher::disableStatusMessages() {
    statusMessageEnabled = false;
}

Philosopher::~Philosopher() {
    stop();
    if (thr.joinable()) {
        thr.join();
    }
    std::string totalTime = std::to_string(stopwatch.getTotalElapsedTime().count());
    std::string averageTime = std::to_string(stopwatch.getAverageTime().count());
    statusForced("ate " + std::to_string(meals) + " times. Waiting time = " +
                 totalTime.erase(totalTime.size() - 4) +
                 "ms (Average = " + averageTime.erase(averageTime.size() - 4) + "ms).");
}

void Philosopher::think() {
    status("is thinking");
    std::this_thread::sleep_for(10ms);
}

void Philosopher::run() {
    while (!paused) {
        think();
        if (paused) {   // temporary workaround, there is a bug, which might cause memory access violation
            return;
        }
        eat();
    }
}

void Philosopher::status(const std::string &str) const {
    if (!statusMessageEnabled) {
        return;
    }
    std::lock_guard<std::mutex> lck(CoutLock::getCoutMutex());
    std::cout << *this << " " << str << std::endl;
}

void Philosopher::statusForced(const std::string &str) const {
    std::lock_guard<std::mutex> lck(CoutLock::getCoutMutex());
    std::cout << *this << " " << str << std::endl;
}


std::ostream &operator<<(std::ostream &os, const Philosopher &philosopher) {
    os << "Philosopher " << philosopher.id;
    return os;
}
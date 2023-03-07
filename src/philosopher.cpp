#include "../include/philosopher.hpp"

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

void Philosopher::think() {
    status("is thinking");
    std::this_thread::sleep_for(10ms);
}

void Philosopher::run() {
    while (!paused) {
        think();
        eat();
    }
}

void Philosopher::status(const std::string &str) const {
    if (!statusMessageEnabled) {
        return;
    }
    std::lock_guard<std::mutex> lck(CoutLock::instance().get_mutex());
    std::cout << *this << " " << str << std::endl;
}


std::ostream &operator<<(std::ostream &os, const Philosopher &philosopher) {
    os << "Philosopher " << philosopher.id;
    return os;
}
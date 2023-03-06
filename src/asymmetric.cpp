//  Asymmetric solution for Dining Philosophers problem is using a method, where each philosopher is given a number.
//  If their number is even, they pick up left fork first. Philosophers with odd number pick right fork instead.
//  This method is preventing deadlocks and starvation, but if there is odd number of philosophers, it may cause
//  uneven distribution of meals between them.

#include "../include/asymmetric.hpp"

Asymmetric::Asymmetric(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right)
        : Philosopher(id, std::move(left), std::move(right)) {};

void Asymmetric::eat() {
    auto start = std::chrono::high_resolution_clock::now();
    if (id % 2 == 0) {
        std::lock_guard<std::mutex> lck(leftFork->mutex);
        std::lock_guard<std::mutex> rck(rightFork->mutex);
        auto end = std::chrono::high_resolution_clock::now();
        waitingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        status("is eating");
        meals++;
        std::this_thread::sleep_for(10ms);

    } else {
        std::lock_guard<std::mutex> rck(rightFork->mutex);
        std::lock_guard<std::mutex> lck(leftFork->mutex);
        auto end = std::chrono::high_resolution_clock::now();
        waitingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        status("is eating");
        meals++;
        std::this_thread::sleep_for(10ms);
    }
}

Asymmetric::~Asymmetric() {
    stop();
    if (thr.joinable()) {
        thr.join();
    }
    enableStatusMessages();
    status("ate " + std::to_string(meals) + " times. Average waiting time = " + std::to_string(waitingTime / meals) +
           "ms");
}
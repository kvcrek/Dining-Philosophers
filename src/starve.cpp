//  This solution is using a method, where the philosophers are checking if both forks are available.
//  If they are available they pick them both simultaneously.
//  This method prevents deadlocks, but allows for starvation of philosophers in specific case, where one or another
//  of their neighbors are eating repeatedly.

#include "../include/starve.hpp"

Starve::Starve(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right)
        : Philosopher(id, std::move(left), std::move(right)) {}

void Starve::eat() {
    stopwatch.start();
    std::lock(leftFork->mutex, rightFork->mutex);
    std::lock_guard<std::mutex> lck(leftFork->mutex, std::adopt_lock);
    std::lock_guard<std::mutex> rck(rightFork->mutex, std::adopt_lock);
    stopwatch.stop();
    status("is eating");
    meals++;
    std::this_thread::sleep_for(10ms);
}

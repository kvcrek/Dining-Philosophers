//  In order to prevent 'naive' solution from deadlocking, it is possible to use a semaphore, called arbiter
//  in this solution. The arbiter makes sure that (n-1) philosophers are trying to eat at the same time. If all the
//  philosophers tries to eat at the same time, one of them will have to wait until someone else finishes eating.

#include "../include/arbiter.hpp"

sem_t Arbiter::arbiter;

Arbiter::Arbiter(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right)
        : Philosopher(id, std::move(left), std::move(right)) {
    sem_destroy(&arbiter);
    sem_init(&arbiter, 0, id - 1);
}

void Arbiter::eat() {
    auto start = std::chrono::high_resolution_clock::now();
    sem_wait(&arbiter);
    std::lock_guard<std::mutex> lck(leftFork->mutex);
    std::lock_guard<std::mutex> rck(rightFork->mutex);
    auto end = std::chrono::high_resolution_clock::now();
    waitingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    status("is eating");
    meals++;
    std::this_thread::sleep_for(10ms);
    sem_post(&arbiter);
}

Arbiter::~Arbiter() {
    stop();
    if (thr.joinable()) {
        thr.join();
    }
    enableStatusMessages();
    status("ate " + std::to_string(meals) + " times. Average waiting time = " + std::to_string(waitingTime / meals) +
           "ms");
}
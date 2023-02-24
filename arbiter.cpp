//  In order to prevent 'naive' solution from deadlocking, it is possible to use a semaphore, called arbiter
//  in this solution. The arbiter makes sure that (n-1) philosophers are trying to eat at the same time. If all the
//  philosophers tries to eat at the same time, one of them will have to wait until someone else finishes eating.

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <semaphore>

using namespace std::chrono_literals;
std::mutex m_cout;
sem_t arbiter;
static bool paused = true;

class Fork {
public:
    std::mutex mutex;

    explicit Fork(int id) {
        this->id = id;
    }

    friend std::ostream &operator<<(std::ostream &os, const Fork &fork);

private:
    int id;
};

std::ostream &operator<<(std::ostream &os, const Fork &fork) {
    os << "Fork " << fork.id;
    return os;
}

class Philosopher {
public:
    explicit Philosopher(int id, Fork &left, Fork &right, std::mutex &cout_lock)
            : id(id),
              leftFork(left),
              rightFork(right),
              cout_lock(cout_lock) {
        meals = 0;
        paused = false;
        thr.detach();
    }

    ~Philosopher() {
        status("ate " + std::to_string(meals) + " times");
    }

    void run() {
        while (!paused) {
            think();
            if (paused) {
                return;
            }
            eat();
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Philosopher &philosopher);

private:
    void status(const std::string &str) {
        std::lock_guard<std::mutex> lck(cout_lock);
        std::cout << *this << " " << str << std::endl;
    }

    void think() {
        status("is thinking");
        std::this_thread::sleep_for(10ms);
    }

    void eat() {
        sem_wait(&arbiter);
        std::lock_guard<std::mutex> lck(leftFork.mutex);
        std::lock_guard<std::mutex> rck(rightFork.mutex);
        if (paused) {
            return;
        }
        status("is eating");
        meals++;
        std::this_thread::sleep_for(10ms);
        sem_post(&arbiter);
    }

    std::mutex &cout_lock;
    std::thread thr = std::thread(&Philosopher::run, this);
    int id;
    int meals;
    Fork &leftFork;
    Fork &rightFork;
};

std::ostream &operator<<(std::ostream &os, const Philosopher &philosopher) {
    os << "Philosopher " << philosopher.id;
    return os;
}

template<typename T>
void startDining(int n, T time) {
    sem_init(&arbiter, 0, n - 1);
    std::vector<Fork *> forks(n);
    std::vector<Philosopher *> philosophers(n);
    paused = false;
    for (int i = 0; i < n; i++) {
        forks[i] = new Fork(Fork(i + 1));
    }

    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            philosophers[i] = new Philosopher(i + 1, *forks[i], *forks[0], m_cout);
        } else {
            philosophers[i] = new Philosopher(i + 1, *forks[i], *forks[i + 1], m_cout);
        }
    }

    std::this_thread::sleep_for(time);
    for (auto *p: philosophers) {
        delete p;
    }
    philosophers.clear();
    for (auto *p: forks) {
        delete p;
    }
    forks.clear();
    paused = true;
}

int main() {
    int n = 12; //number of philosophers
    startDining(n, 5s);

    return 0;
}
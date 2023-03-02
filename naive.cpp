//  This solution is using 'naive' method, where each philosopher picks up the fork on his left, and then on his right.
//  If fork cannot be picked up, he waits for the other philosopher to finish eating.
//  Note that, this solution can enter a state, where all philosophers picked up their left fork at the same time, it
//  can enter a state, where no action is made since all of them are waiting their right forks resulting in deadlock.

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

using namespace std::chrono_literals;
std::mutex m_cout;

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
        paused = true;
    }

    void start(){
        paused = false;
    }

    void stop(){
        paused = true;
        if(thr.joinable()){
        thr.join();
        }
    }

    ~Philosopher() {
        status("ate " + std::to_string(meals) + " times");
    }


    friend std::ostream &operator<<(std::ostream &os, const Philosopher &philosopher);

private:
    void run() {
        while (!paused) {
            think();
            eat();
        }
    }

    void status(const std::string &str) {
        std::lock_guard<std::mutex> lck(cout_lock);
        std::cout << *this << " " << str << std::endl;
    }

    void think() {
        status("is thinking");
        std::this_thread::sleep_for(10ms);
    }

    void eat() {
        std::lock_guard<std::mutex> lck(leftFork.mutex);
        std::lock_guard<std::mutex> rck(rightFork.mutex);
        status("is eating");
        meals++;
        std::this_thread::sleep_for(10ms);
    }

    bool paused;
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
    std::vector<Fork *> forks(n);
    std::vector<Philosopher *> philosophers(n);

    for (int i = 0; i < n; i++) {
        forks[i] = new Fork(Fork(i + 1));
    }
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            philosophers[i] = new Philosopher(i + 1, *forks[i], *forks[0], m_cout);
        } else {
            philosophers[i] = new Philosopher(i + 1, *forks[i], *forks[i + 1], m_cout);
        }
        philosophers[i]->start();
    }

    std::this_thread::sleep_for(time);
    for (auto *p: philosophers) {
        p->stop();
    }
    for (auto *p: philosophers) {
        delete p;
    }
    philosophers.clear();
    for (auto *p: forks) {
        delete p;
    }
    forks.clear();
}

int main() {
    int n = 12; //number of philosophers
    startDining(n, 5s);

    return 0;
}
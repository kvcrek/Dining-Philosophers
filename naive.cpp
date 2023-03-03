//  This solution is using 'naive' method, where each philosopher picks up the fork on his left, and then on his right.
//  If fork cannot be picked up, he waits for the other philosopher to finish eating.
//  Note that, this solution can enter a state, where all philosophers picked up their left fork at the same time, it
//  can enter a state, where no action is made since all of them are waiting their right forks resulting in deadlock.

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <memory>

using namespace std::chrono_literals;
std::mutex m_cout;

class Fork : public std::enable_shared_from_this<Fork>  {
public:
    std::mutex mutex;

    std::shared_ptr<Fork> getptr(){
        return shared_from_this();
    }

    [[nodiscard]] static std::shared_ptr<Fork> create(){
        return std::shared_ptr<Fork>(new Fork);
    }

private:
    Fork() = default;
};

class Philosopher {
public:
    explicit Philosopher(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right, std::mutex &cout_lock)
        : id(id),
        cout_lock(cout_lock),
        leftFork(std::move(left)),
        rightFork(std::move(right)) {
        meals = 0;
        waitingTime = 0;
    }

    void start() {
        paused = false;
    }

    void stop() {
        paused = true;
        if(thr.joinable()){
        thr.join();
        }
    }

    ~Philosopher() {
        status("ate " + std::to_string(meals) + " times. Average waiting time = " + std::to_string(waitingTime/meals) + "ms");
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
        auto start = std::chrono::high_resolution_clock::now();
        std::lock_guard<std::mutex> lck(leftFork->mutex);
        std::lock_guard<std::mutex> rck(rightFork->mutex);
        auto end = std::chrono::high_resolution_clock::now();
        waitingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        status("is eating");
        meals++;
        std::this_thread::sleep_for(10ms);
    }

    bool paused = true;
    std::mutex &cout_lock;
    std::thread thr = std::thread(&Philosopher::run, this);
    int id;
    int meals;
    std::shared_ptr<Fork> leftFork;
    std::shared_ptr<Fork> rightFork;
    long long int waitingTime;
};

std::ostream &operator<<(std::ostream &os, const Philosopher &philosopher) {
    os << "Philosopher " << philosopher.id;
    return os;
}

template<typename T>
void startDining(int n, T time) {
    std::vector<std::shared_ptr<Fork>> forks;
    std::vector<std::unique_ptr<Philosopher>> philosophers;
    forks.reserve(n);
    philosophers.reserve(n);

    for (int i = 0; i < n; i++) {
        forks.push_back(Fork::create());
    }
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            philosophers.push_back(std::make_unique<Philosopher>(i + 1, forks[i]->getptr(), forks[0]->getptr(), m_cout));
        } else {
            philosophers.push_back(std::make_unique<Philosopher>(i + 1, forks[i]->getptr(), forks[i+1]->getptr(), m_cout));
        }
        philosophers[i]->start();
    }
    std::this_thread::sleep_for(time);
    for(auto &var : philosophers) {
        var->stop();
    }
}

int main() {
    int n = 12; //number of philosophers
    startDining(n, 5s);

    return 0;
}
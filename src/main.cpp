#include <iostream>
#include <vector>

#include "../include/naive.hpp"
#include "../include/starve.hpp"
#include "../include/asymmetric.hpp"
#include "../include/arbiter.hpp"

template<typename T>
std::enable_if_t<std::is_base_of_v<Philosopher, T>, void>
startDining(int n) {
    std::vector<std::shared_ptr<Fork>> forks;
    std::vector<std::unique_ptr<Philosopher>> philosophers;
    forks.reserve(n);
    philosophers.reserve(n);

    for (int i = 0; i < n; i++) {
        forks.push_back(Fork::create());
    }
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            philosophers.push_back(std::make_unique<T>(i + 1, forks[i]->getptr(), forks[0]->getptr()));
        } else {
            philosophers.push_back(std::make_unique<T>(i + 1, forks[i]->getptr(), forks[i + 1]->getptr()));
        }
        philosophers[i]->disableStatusMessages();
        philosophers[i]->start();
    }
    std::this_thread::sleep_for(5s);
    for (auto &var: philosophers) {
        var->stop();
    }
}


int main() {

    int n = 5;
    std::cout << "Number of philosophers is set to " << n << std::endl;
    std::cout << "Starting Naive solution" << std::endl;
    startDining<Naive>(n);
    std::cout << "Starting Starve solution" << std::endl;
    startDining<Starve>(n);
    std::cout << "Starting Asymmetric solution" << std::endl;
    startDining<Asymmetric>(n);
    std::cout << "Starting Arbiter solution" << std::endl;
    startDining<Arbiter>(n);
    std::cout << "--- Finished ---" << std::endl;

    return 0;
}

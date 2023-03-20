#include <benchmark/benchmark.h>
#include <vector>
#include "naive.hpp"
#include "fork.hpp"

int n = 10;

static void BM_PtrAllocation(benchmark::State &state) {
    Philosopher::disableStatusMessages();
    Philosopher::disableDestructorMessages();
    for (auto _: state) {

        std::vector<std::shared_ptr<Fork>> forks;
        std::vector<std::unique_ptr<Naive>> philosophers;
        forks.reserve(n);
        philosophers.reserve(n);

        for (int i = 0; i < n; i++) {
            forks.push_back(Fork::create());
        }
        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                philosophers.push_back(std::make_unique<Naive>(i + 1, forks[i]->getptr(), forks[0]->getptr()));
            } else {
                philosophers.push_back(std::make_unique<Naive>(i + 1, forks[i]->getptr(), forks[i + 1]->getptr()));
            }
        }
    }
}

BENCHMARK(BM_PtrAllocation);

BENCHMARK_MAIN();
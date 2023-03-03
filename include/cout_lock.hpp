#pragma once

#include <thread>

class CoutLock {
public:
    static CoutLock &instance();

    std::mutex &get_mutex();

    CoutLock(const CoutLock &) = delete;

    CoutLock &operator=(const CoutLock &) = delete;

private:
    CoutLock() = default;

    ~CoutLock() = default;

    std::mutex m;
};


CoutLock &CoutLock::instance() {
    static CoutLock instance;
    return instance;
}

std::mutex &CoutLock::get_mutex() {
    return m;
}
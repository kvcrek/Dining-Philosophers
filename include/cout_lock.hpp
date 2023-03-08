#pragma once

#include <mutex>

class CoutLock {
public:
    static CoutLock &instance();

    std::mutex &get_mutex();

    CoutLock(const CoutLock &) = delete;

    CoutLock &operator=(const CoutLock &) = delete;

    CoutLock(CoutLock &&) = delete;

    CoutLock &operator=(CoutLock &&) = delete;

private:
    CoutLock() = default;

    ~CoutLock() = default;

    std::mutex m;
};
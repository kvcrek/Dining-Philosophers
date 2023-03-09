#pragma once

#include <mutex>

class CoutLock {
public:
    static std::mutex &getCoutMutex();

    CoutLock(const CoutLock &) = delete;

    CoutLock &operator=(const CoutLock &) = delete;

    CoutLock(CoutLock &&) = delete;

    CoutLock &operator=(CoutLock &&) = delete;

private:
    CoutLock() = default;

    ~CoutLock() = default;

    static std::mutex m;
};
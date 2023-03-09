#include "cout_lock.hpp"

std::mutex &CoutLock::getCoutMutex() {
    static std::mutex m;
    return m;
}
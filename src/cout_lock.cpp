#include "cout_lock.hpp"

std::mutex CoutLock::m;

std::mutex &CoutLock::getCoutMutex() {
    return m;
}
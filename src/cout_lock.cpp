#include "../include/cout_lock.hpp"


CoutLock &CoutLock::instance() {
    static CoutLock instance;
    return instance;
}

std::mutex &CoutLock::get_mutex() {
    return m;
}
#include "fork.hpp"

std::shared_ptr<Fork> Fork::getptr() {
    return shared_from_this();
}

std::shared_ptr<Fork> Fork::create() {
    return std::shared_ptr<Fork>(new Fork);
}
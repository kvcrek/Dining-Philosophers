#pragma once

#include "philosopher.hpp"

class Naive : public Philosopher {
public:
    explicit Naive(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);

private:
    void eat() override;
};

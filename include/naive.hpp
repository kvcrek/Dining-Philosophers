#pragma once

#include "philosopher.hpp"

class Naive : public virtual Philosopher {
public:
    explicit Naive(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);

    ~Naive();

private:
    void eat() override;
};

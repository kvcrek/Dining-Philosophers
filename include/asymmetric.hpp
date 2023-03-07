#pragma once

#include "philosopher.hpp"

class Asymmetric : public Philosopher {
public:
    explicit Asymmetric(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);

private:
    void eat() override;
};
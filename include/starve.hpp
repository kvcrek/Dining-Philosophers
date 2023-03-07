#pragma once

#include "philosopher.hpp"

class Starve : public Philosopher {
public:
    explicit Starve(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);


private:
    void eat() override;
};
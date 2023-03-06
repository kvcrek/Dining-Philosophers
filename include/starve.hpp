#pragma once

#include "philosopher.hpp"

class Starve : public virtual Philosopher {
public:
    explicit Starve(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);

    ~Starve();

private:
    void eat() override;
};
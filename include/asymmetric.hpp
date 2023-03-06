#pragma once

#include "philosopher.hpp"

class Asymmetric : public virtual Philosopher {
public:
    explicit Asymmetric(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);

    ~Asymmetric();

private:
    void eat() override;
};
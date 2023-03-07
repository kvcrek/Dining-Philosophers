#pragma once

#include "philosopher.hpp"

class Arbiter : public Philosopher {
public:
    explicit Arbiter(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);

private:
    void eat() override;

    static sem_t arbiter;
};
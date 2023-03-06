#pragma once

#include "philosopher.hpp"


class Arbiter : public virtual Philosopher {
public:
    explicit Arbiter(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);

    ~Arbiter();

private:
    void eat() override;

    static sem_t arbiter;
};
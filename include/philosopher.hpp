#pragma once

#include <iostream>
#include <thread>
#include <chrono>

#include "cout_lock.hpp"
#include "fork.hpp"
#include "stopwatch.hpp"

using namespace std::chrono_literals;

class Philosopher {
public:
    explicit Philosopher(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right);

    void start();

    void stop();

    static void enableStatusMessages();

    static void disableStatusMessages();

    static void enableDestructorMessages();

    static void disableDestructorMessages();

    virtual ~Philosopher();

    friend std::ostream &operator<<(std::ostream &os, const Philosopher &philosopher);


protected:
    void run();

    void status(const std::string &str) const;

    void destructorMessage(const std::string &str) const;

    void think();

    virtual void eat() = 0;

    static bool statusMessageEnabled;
    static bool destructorMessagesEnabled;
    bool paused;
    std::thread thr;
    int id;
    int meals;
    std::shared_ptr<Fork> leftFork;
    std::shared_ptr<Fork> rightFork;
    Stopwatch stopwatch;
};
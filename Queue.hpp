#ifndef QUEUE_HPP
#define QUEUE_HPP 

#include <iostream>
#include <memory>

#include "Workers/WorkerPool.hpp"

class Queue {
    public:
        Queue();
        void run();

    private:
        std::unique_ptr<WorkerPool> pool_;
};

#endif

#ifndef WORKER_HPP
#define WORKER_HPP

#include <iostream>
#include <mutex>
#include <condition_variable> 

#include "WorkerPool.hpp"
#include "WorkerJob.hpp"

class WorkerPool;
class WorkerJob;

class Worker {
    public:
        Worker(WorkerPool& pool, std::mutex* mtx, std::condition_variable* cv);
        void work();

    private:
        void run(std::unique_ptr<WorkerJob> job);

    private:
        WorkerPool& pool_;
        std::mutex* mtx_;
        std::condition_variable* cv_;
};

#endif

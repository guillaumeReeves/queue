#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include <thread>
#include <mutex>
#include <condition_variable> 
#include <iostream>
#include <deque>

#include "Worker.hpp"
#include "WorkerJob.hpp"
#include "SampleJob.hpp"

class WorkerJob;
class Worker;
class SampleJob;

struct JobData {
    uint32_t type;
    std::string data;
};

class WorkerPool {
    public:
        WorkerPool(uint32_t threadQty);
        bool init();
        void addJob(uint32_t type, std::string data);

        bool jobAvailable();
        std::unique_ptr<WorkerJob> getJob();

        enum JobType {
            SAMPLE_JOB = 1,
        };


    private:
        uint32_t threadQty_;
        std::mutex mtx_;
        std::condition_variable cv_;

        std::deque<Worker> workers_;
        std::deque<JobData> works_;
        std::deque<std::thread*> worker_threads_;
};

#endif

#ifndef WORKER_JOB_HPP
#define WORKER_JOB_HPP 

#include <iostream>
#include <string>
#include <thread>

class WorkerJob {
    public:
        WorkerJob();
        virtual ~WorkerJob();
        virtual void execute() = 0;
        virtual void setData(std::string data) = 0;

};

#endif

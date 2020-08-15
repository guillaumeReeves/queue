#ifndef SAMPLE_JOB_HPP
#define SAMPLE_JOB_HPP

#include <chrono>

#include "WorkerJob.hpp"

class SampleJob: public WorkerJob {
    public:
        SampleJob();
        ~SampleJob();
        void execute();
        void setData(std::string sampleData); 

    private:
        std::string sampleData_;
};

#endif

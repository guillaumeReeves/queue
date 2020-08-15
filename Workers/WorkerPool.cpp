#include "WorkerPool.hpp"

WorkerPool::WorkerPool(uint32_t threadQty) : threadQty_(threadQty) {}

bool WorkerPool::init() {

    // Create the worker threads to handle jobs
    for(uint32_t i = 0; i < threadQty_; i++) {
        Worker worker(*this, &mtx_, &cv_);
        workers_.push_back(worker);

        std::thread* t = new std::thread (&Worker::work, worker);

        t->detach();

        worker_threads_.push_back(t);
    }

    return true;
}

void WorkerPool::addJob(uint32_t type, std::string data) {
    JobData jd;
    jd.type = type;
    jd.data = data;

    // lock for safety
    std::unique_lock<std::mutex> lck(mtx_);

    // Add the data to the deque
    works_.push_back(jd);

    // Unlock
    lck.unlock();

    // Notify job available
    cv_.notify_all();
}

bool WorkerPool::jobAvailable() {
    return works_.size() > 0;
}

std::unique_ptr<WorkerJob> WorkerPool::getJob() {
    JobData jd = works_.front();
    works_.pop_front();

    std::unique_ptr<WorkerJob> job;
    switch(jd.type) {
        case JobType::SAMPLE_JOB:
            job = std::unique_ptr<WorkerJob>(new SampleJob());
            job->setData(jd.data);
            break;
        default:
            return nullptr;
    }

    return std::move(job);
}

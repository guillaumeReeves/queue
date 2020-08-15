#include "Worker.hpp"

Worker::Worker(WorkerPool& pool, std::mutex* mtx, std::condition_variable* cv) : pool_(pool), mtx_(mtx), cv_(cv) {}

void Worker::run(std::unique_ptr<WorkerJob> job) {
    job->execute();
}

void Worker::work() {
    while(1) {
        // Lock for safety
        std::unique_lock<std::mutex> lck(*mtx_);

        // Wait for notification that there is data to be consumed
        cv_->wait(lck, [this] { return pool_.jobAvailable(); });

        // Retrieve the next data to be consumed and remove it from array
        std::unique_ptr<WorkerJob> job = pool_.getJob();

        lck.unlock();

        if(job != nullptr) { // if a wrong job type is given, it would return nullptr
            run(std::move(job));
        }
    }
}



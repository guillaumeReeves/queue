#include "Queue.hpp" 

Queue::Queue() {
    // TODO: Move hardcoded thread count to config or env file
    pool_ = std::unique_ptr<WorkerPool> { new WorkerPool(4) };

    if(!pool_->init()) {
        std::cerr << "{AppName} Couldn't create worker pool instance, EXITING" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Queue::run() {
    while(1) {
        //TODO: Implement Libevent server to listen for incoming jobs

        // Add block to be parsed to parse jobs queue
        pool_->addJob(pool_->JobType::SAMPLE_JOB, "sample data");

        //  Add wait until the Libevent server is implemented
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }


}

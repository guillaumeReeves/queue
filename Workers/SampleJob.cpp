#include "SampleJob.hpp"

SampleJob::SampleJob() {}

SampleJob::~SampleJob() {}

void SampleJob::setData(std::string sampleData) {
    sampleData_ = sampleData;
}

void SampleJob::execute() {
    std::cout << "Executing job with data: " << sampleData_ << std::endl;
}

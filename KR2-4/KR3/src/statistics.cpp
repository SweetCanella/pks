#include "statistics.h"

#include <algorithm>
#include <numeric>
#include <sstream>

#include "request.h"

namespace elevator_sim {

void Statistics::registerElevator(int elevatorId) {
    std::lock_guard<std::mutex> lock(mtx_);
    servedByElevator_.emplace(elevatorId, 0);
}

void Statistics::onCompleted(const Request& /*request*/,
                             std::chrono::milliseconds waitTime) {
    std::lock_guard<std::mutex> lock(mtx_);
    waitTimesMs_.push_back(waitTime.count());
}

void Statistics::onServed(int elevatorId) {
    std::lock_guard<std::mutex> lock(mtx_);
    servedByElevator_[elevatorId] += 1;
}

std::string Statistics::report() const {
    std::lock_guard<std::mutex> lock(mtx_);

    std::ostringstream oss;
    oss << "[Statistics] Total processed: " << waitTimesMs_.size() << '\n';

    if (!waitTimesMs_.empty()) {
        long long sum = std::accumulate(waitTimesMs_.begin(),
                                        waitTimesMs_.end(), 0LL);
        long long maxWait = *std::max_element(waitTimesMs_.begin(),
                                              waitTimesMs_.end());
        oss << "[Statistics] Average wait: "
            << (sum / static_cast<long long>(waitTimesMs_.size()))
            << " ms\n";
        oss << "[Statistics] Maximum wait: " << maxWait << " ms\n";
    }

    for (const auto& [id, count] : servedByElevator_) {
        oss << "[Statistics] Elevator " << id
            << " served " << count << " request(s)\n";
    }

    return oss.str();
}

}  // namespace elevator_sim

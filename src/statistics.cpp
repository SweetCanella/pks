#include "statistics.h"

#include <algorithm>
#include <numeric>
#include <sstream>

#include "request.h"

void Statistics::registerElevator(int elevatorId) {
    servedByElevator_.emplace(elevatorId, 0);
}

void Statistics::onCompleted(const Request&, std::chrono::milliseconds waitTime) {
    waitTimesMs_.push_back(waitTime.count());
}

void Statistics::onServed(int elevatorId) {
    servedByElevator_[elevatorId] += 1;
}

std::string Statistics::report() const {
    std::ostringstream oss;
    oss << "[Statistics] Total processed: " << waitTimesMs_.size() << '\n';

    if (!waitTimesMs_.empty()) {
        long long sum = std::accumulate(waitTimesMs_.begin(), waitTimesMs_.end(), 0LL);
        long long maxWait = *std::max_element(waitTimesMs_.begin(), waitTimesMs_.end());
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

#pragma once

#include <optional>
#include <queue>
#include <utility>

template <typename T>
class SimpleQueue {
public:
    void push(T value) {
        queue_.push(std::move(value));
    }

    std::optional<T> pop() {
        if (queue_.empty()) {
            return std::nullopt;
        }

        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    bool empty() const {
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
};

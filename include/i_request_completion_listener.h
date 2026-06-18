#pragma once

#include <chrono>

struct Request;

struct IRequestCompletionListener {
    virtual ~IRequestCompletionListener() = default;

    virtual void onCompleted(const Request& request, std::chrono::milliseconds waitTime) = 0;
};

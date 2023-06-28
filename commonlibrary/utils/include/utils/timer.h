#ifndef UTILS_TIMER_H
#define UTILS_TIMER_H

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace EL {
namespace Utils {

class Timer {
public:
    Timer() : stopStatus_(true), tryStopFlag_(false) {}

    Timer(const Timer &timer)
    {
        stopStatus_ = timer.stopStatus_.load();
        tryStopFlag_ = timer.tryStopFlag_.load();
    }

    ~Timer()
    {
        stop();
    }

    void start(int interval, std::function<void()> taskFun)
    {
        if (stopStatus_ == false) {
            return;
        }
        stopStatus_ = false;
        std::thread([this, interval, taskFun]() {
            while (!tryStopFlag_) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                taskFun();
            }

            {
                std::lock_guard<std::mutex> locker(mutex_);
                stopStatus_ = true;
                tryStopFlag_ = false;
                timerCond_.notify_one();
            }
        }).detach();
    }

    void stop()
    {
        if (stopStatus_ || tryStopFlag_) {
            return;
        }
        tryStopFlag_ = true;
        {
            std::unique_lock<std::mutex> locker(mutex_);
            timerCond_.wait(locker, [this] { return stopStatus_ == true; });

            if (stopStatus_ == true)
                tryStopFlag_ = false;
        }
    }

    void ThreadExit()
    {
        std::lock_guard<std::mutex> locker(mutex_);
        stopStatus_ = true;
        tryStopFlag_ = true;
    }

private:
    std::atomic<bool> stopStatus_;
    std::atomic<bool> tryStopFlag_;
    std::mutex mutex_;
    std::condition_variable timerCond_;
};
} // namespace Utils
} // namespace EL

#endif // UTILS_TIMER_H
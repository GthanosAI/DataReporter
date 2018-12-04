#include <chrono>
#include <mutex>
#include "NanoTime.h"


namespace future {
    std::mutex NANO_TIME_GUARD_LOCK;
    static std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> MONOTONIC_START_TIME(
            std::chrono::steady_clock::now());

    static std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> NOW_START_TIME(
            std::chrono::system_clock::now());

    std::int64_t GetNanoTime(void) {
        std::lock_guard<std::mutex> lock(NANO_TIME_GUARD_LOCK);
        std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> lapseTime = std::chrono::time_point_cast<std::chrono::nanoseconds>(
                std::chrono::steady_clock::now());
        std::int64_t nanoTime =
                NOW_START_TIME.time_since_epoch().count() + lapseTime.time_since_epoch().count() - MONOTONIC_START_TIME.time_since_epoch().count();
        return nanoTime;
    }
}

//
// Created by marceli on 18.01.20.
//

#include "Timer.h"
Timer::Timer(unsigned long long tSeconds) : start_time(std::chrono::steady_clock::now()), end_time(std::chrono::steady_clock::now()) {
    if (alarm > 0) {
        alarm = tSeconds;
    }
    else{
        alarm = DEFAULT_ALARM;
    }
    prev_duration = 0;
}
bool Timer::checkAlarm() {
    end_time = std::chrono::steady_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    if (prev_duration != duration) {
        prev_duration = duration;
        std::cout << duration << std::endl;
    }
    return duration >= alarm;
}
void Timer::reset() {
    start_time = std::chrono::steady_clock::now();
    end_time = std::chrono::steady_clock::now();
}
bool Timer::setAlarm(unsigned long long tSeconds) {
    if (tSeconds > 0) {
        alarm = tSeconds;
        return true;
    }
    return false;
}
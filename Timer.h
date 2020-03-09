//
// Created by marceli on 18.01.20.
//

#ifndef THEBIGESTPROJECT_TIMER_H
#define THEBIGESTPROJECT_TIMER_H
#include <chrono>
#include <iostream>
unsigned long long const DEFAULT_ALARM = 10;
class Timer {
public:
    explicit Timer(unsigned long long tSeconds);
    bool setAlarm(unsigned long long tSeconds);
    bool checkAlarm();
    void reset();
private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::chrono::time_point<std::chrono::steady_clock> end_time;
    unsigned long long alarm;
    unsigned long long prev_duration;
};


#endif //THEBIGESTPROJECT_TIMER_H

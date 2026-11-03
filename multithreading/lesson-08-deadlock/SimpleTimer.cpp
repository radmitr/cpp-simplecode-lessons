// C++11 — измерение времени через std::chrono.
#include "SimpleTimer.hpp"

#include <chrono>
#include <iostream>

SimpleTimer::SimpleTimer()
{
    start = std::chrono::high_resolution_clock::now();
}

SimpleTimer::~SimpleTimer()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float result = duration.count();
    std::cout << "DURATION: " << result << "s" << std::endl;
}

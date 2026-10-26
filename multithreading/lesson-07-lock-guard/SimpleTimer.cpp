#include "SimpleTimer.hpp"

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

// C++11 — steady_clock и deque; сетевые политики — token bucket и ограниченная очередь.
#include <algorithm>
#include <chrono>
#include <deque>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "../../../basics/additions/common/check.hpp"

class Bucket
{
    double tokens_ = 2;
    std::chrono::steady_clock::time_point updated_;
public:
    explicit Bucket(std::chrono::steady_clock::time_point now) : updated_(now) {}
    bool admit(std::chrono::steady_clock::time_point now)
    {
        if (now < updated_) throw std::invalid_argument("clock moved backwards");
        tokens_ = std::min(2.0, tokens_ + std::chrono::duration<double>(now - updated_).count());
        updated_ = now;
        if (tokens_ < 1) return false;
        tokens_ -= 1;
        return true;
    }
};
int main()
{
    try
    {
        using namespace std::chrono;
        const steady_clock::time_point start{};
        Bucket bucket(start);
        check(bucket.admit(start) && bucket.admit(start) && !bucket.admit(start), "burst capacity");
        check(!bucket.admit(start + milliseconds(999)) && bucket.admit(start + seconds(1)), "refill");
        std::deque<int> pending;
        auto enqueue = [&](int value) {
            if (pending.size() == 2) return false;
            pending.push_back(value);
            return true;
        };
        check(enqueue(1) && enqueue(2) && !enqueue(3), "bounded admission");
        pending.pop_front();
        check(enqueue(3) && pending.front() == 2, "resume admission after drain");
        std::cout << "burst=2 refill=1/s queue=2\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

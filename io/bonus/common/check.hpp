// C++98 — throw и std::runtime_error.
#pragma once
#include <iostream>
#include <stdexcept>

inline void check(bool condition, const char* message)
{
    if (!condition)
        throw std::runtime_error(message);
}

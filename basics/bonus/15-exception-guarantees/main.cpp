#include <vector>
#include <stdexcept>
#include "../common/check.hpp"

void append_checked(std::vector<int>& data, int value)
{
    auto candidate = data;
    candidate.push_back(value);
    if (value < 0) throw std::invalid_argument("negative value");
    data.swap(candidate);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        std::vector<int> data{1, 2};
        const auto before = data;
        bool rejected = false;
        try { append_checked(data, -1); }
        catch (const std::invalid_argument&) { rejected = true; }
        check(rejected && data == before, "strong guarantee broken");
        append_checked(data, 3);
        check(data == std::vector<int>({1, 2, 3}), "commit failed");
        std::cout << "prepare, validate, commit\n";
        std::cout << "OK 15-exception-guarantees\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

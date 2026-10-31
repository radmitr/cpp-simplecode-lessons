#include <string>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        int value = 7;
        int& alias = value;
        const int& observed = value;
        alias = 9;
        check(observed == 9, "reference is not a snapshot");
        const std::string& temporary = std::string("extended lifetime");
        check(temporary.size() == 17, "temporary lifetime failed");
        int* pointer = nullptr;
        check(pointer == nullptr, "nullable pointer expected");
        pointer = &value;
        std::cout << *pointer << ' ' << temporary << '\n';
        std::cout << "OK 03-references-and-lifetime\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

#include "shared.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        check(shared_answer() == answer_from_other_file(), "translation units disagree");
        check(shared_answer() == 42, "shared header failed");
        std::cout << shared_answer() << '\n';
        std::cout << "OK 24-odr-and-linkage\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

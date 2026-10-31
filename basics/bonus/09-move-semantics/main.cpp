#include <memory>
#include <utility>
#include <string>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        auto first = std::make_unique<int>(7);
        auto&& reference = std::move(first);
        check(first && &reference == &first, "move cast itself transferred ownership");
        auto second = std::move(first);
        check(!first && second && *second == 7, "unique ownership transfer failed");
        std::string text = "payload";
        std::string destination = std::move(text);
        check(destination == "payload", "string move failed");
        text = "reused"; // Не предполагаем, что перемещённая строка обязательно пустая.
        std::cout << *second << ' ' << text << '\n';
        std::cout << "OK 09-move-semantics\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

// C++11 — std::unique_ptr::release() и reset(); C++14 — std::make_unique.
#include <memory>
#include "../common/check.hpp"

int main()
{
    try
    {
        auto first = std::make_unique<int>(42);
        int* raw = first.release(); // first пуст, объект int всё ещё существует.
        std::unique_ptr<int> second(raw); // Сразу назначаем нового владельца.
        check(!first && second && *second == 42, "release changed the object");
        std::cout << "First empty: " << std::boolalpha << !first
                  << "; second: " << *second << '\n';
        second.reset(); // Теперь int уничтожен.
        check(!second, "reset must empty owner");
        std::cout << "OK unique-ptr-release\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

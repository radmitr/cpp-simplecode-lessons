#include <map>
#include <string>
#include "../common/check.hpp"

struct Point { int x; int y; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Point point{1, 2};
        auto [copyX, copyY] = point;
        auto& [x, y] = point;
        x = 9;
        check(copyX == 1 && copyY == 2 && point.x == 9, "binding ownership mismatch");
        using Scores = std::map<std::string, int>;
        Scores scores{{"Ada", 7}};
        for (auto& [name, score] : scores) { score += 1; std::cout << name << '=' << score << '\n'; }
        check(scores.at("Ada") == 8 && y == 2, "map binding failed");
        std::cout << "OK 08-structured-bindings\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

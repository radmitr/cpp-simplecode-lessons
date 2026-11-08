// C++23 — стандартный модуль std и println.
import std;

int main()
{
    try
    {
        std::vector<int> values{1, 2, 3};
        const int total = std::accumulate(values.begin(), values.end(), 0);
        if (total != 6) return 1;
        std::println("sum={}", total);
        std::println("OK reference-example");
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

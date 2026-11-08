// C++23 — std::flat_map и операции над его хранилищем.
#include <exception>
#include <flat_map>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::flat_map<std::string, int> map{{"b", 2}, {"a", 1}};
        check(!map.try_emplace("a", 9).second, "unique key");
        map.insert_or_assign("a", 5);
        map.try_emplace("c", 3);
        check(map.at("a") == 5 && map.contains("b"), "lookup");
        map.erase("b");
        auto storage = std::move(map).extract();
        check(storage.keys == std::vector<std::string>{"a", "c"}, "sorted keys");
        std::flat_map<std::string, int> restored;
        restored.replace(std::move(storage.keys), std::move(storage.values));
        for (auto [key, value] : restored) std::cout << key << '=' << value << ' ' ;
        std::cout << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

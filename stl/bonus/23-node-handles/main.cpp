// C++17 — узлы map: extract, key и insert_return_type.
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <utility>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::map<int, std::unique_ptr<int>> source;
        source.emplace(1, std::make_unique<int>(7));
        std::map<int, std::unique_ptr<int>> target;
        target.emplace(2, std::make_unique<int>(9));
        int* original = source.at(1).get();
        auto node = source.extract(1);
        check(source.empty() && node && node.key() == 1, "extracted ownership");
        node.key() = 2;
        auto rejected = target.insert(std::move(node));
        check(!rejected.inserted && rejected.node && *rejected.position->second == 9, "duplicate keeps node");
        rejected.node.key() = 3;
        auto accepted = target.insert(std::move(rejected.node));
        check(accepted.inserted && accepted.node.empty(), "successful transfer");
        check(accepted.position->second.get() == original && *original == 7, "payload not copied");
        check(source.extract(100).empty(), "missing key");
        std::cout << accepted.position->first << '=' << *accepted.position->second << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

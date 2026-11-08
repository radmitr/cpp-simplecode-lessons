// C++17 — valueless_by_exception при неудачном перемещении variant.
#include <exception>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <variant>

#include "../../../basics/additions/common/check.hpp"

struct FailingMove
{
    FailingMove() = default;
    FailingMove(const FailingMove&) = delete;
    FailingMove(FailingMove&&) { throw std::runtime_error("expected move failure"); }
    FailingMove& operator=(FailingMove&&) = default;
};

int main()
{
    try
    {
        std::variant<int, FailingMove> target(7);
        std::variant<int, FailingMove> source(std::in_place_index<1>);
        bool caught = false;
        try { target = std::move(source); }
        catch (const std::runtime_error&) { caught = true; }
        check(caught && target.valueless_by_exception(), "failed type-changing move assignment");
        check(target.index() == std::variant_npos && !std::get_if<int>(&target), "valueless observers");
        bool visit_rejected = false;
        try { std::visit([](const auto&) {}, target); }
        catch (const std::bad_variant_access&) { visit_rejected = true; }
        check(visit_rejected, "cannot visit a valueless variant");
        target.emplace<int>(9);
        check(std::get<int>(target) == 9, "recover a value");
        std::cout << std::get<int>(target) << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

// C++26 — контракты членов класса (экспериментальная поддержка GCC).
// C++17 — from_chars и optional; C++98 — инвариант объекта.
#include <charconv>
#include <exception>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <system_error>

#include "../../../basics/additions/common/check.hpp"

class Account
{
    int balance_ = 0;
    bool invariant() const noexcept { return balance_ >= 0 && balance_ <= 1000; }
public:
    int balance() const pre(invariant()) { return balance_; }
    void deposit(const int amount) pre(invariant()) pre(amount >= 0 && amount <= 1000)
        post(invariant())
    {
        if (amount > 1000 - balance_) throw std::out_of_range("capacity exceeded");
        balance_ += amount;
    }
};
std::optional<int> parse(std::string_view text)
{
    int value = 0;
    const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
    if (result.ec != std::errc{} || result.ptr != text.data() + text.size()
        || value < 0 || value > 1000) return std::nullopt;
    return value;
}
int main()
{
    try
    {
        Account account;
        for (const auto text : {"25", "-1", "oops", "1001"})
        {
            const auto amount = parse(text);
            if (amount) account.deposit(*amount);
            else std::cout << "rejected: " << text << '\n';
        }
        try { account.deposit(1000); }
        catch (const std::out_of_range&) { std::cout << "capacity exceeded\n"; }
        check(account.balance() == 25, "failed update preserves invariant");
        std::cout << "balance=25\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

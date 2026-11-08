// C++98 — std::ios_base::failure; C++11 — std::system_error и std::future_error.
#include <exception>
#include <future>
#include <iostream>
#include <sstream>
#include <system_error>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        int caught = 0;
        try
        {
            // Явно моделируем ошибку; права настоящих файлов не меняем.
            throw std::system_error(std::make_error_code(std::errc::permission_denied), "demo");
        }
        catch (const std::system_error& error)
        {
            ++caught;
            check(error.code() == std::errc::permission_denied, "wrong error code");
            std::cout << "system_error: permission_denied\n";
        }
        try
        {
            std::istringstream input("not-a-number");
            input.exceptions(std::ios::failbit | std::ios::badbit);
            int value = 0;
            input >> value;
        }
        catch (const std::ios_base::failure&)
        {
            ++caught;
            std::cout << "ios_base::failure\n";
        }
        try
        {
            std::promise<int> sender;
            auto result = sender.get_future();
            (void)sender.get_future(); // Одному promise нельзя дважды выдать future.
        }
        catch (const std::future_error& error)
        {
            ++caught;
            check(error.code() == std::future_errc::future_already_retrieved, "wrong future error");
            std::cout << "future_error: future_already_retrieved\n";
        }
        check(caught == 3, "not all exceptions caught");
        std::cout << "OK error-codes\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

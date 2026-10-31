#include <charconv>
#include <system_error>
#include "../common/reflection.hpp"

struct Settings { int port; int workers; };
template<class T> bool set_option(T& object, std::string_view key, std::string_view text)
{
    bool found = false;
    reflection_demo::for_each_field(object, [&](auto name, auto& field) {
        if (name != key) return;
        int candidate = 0;
        auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), candidate);
        if (error != std::errc{} || end != text.data() + text.size() || candidate <= 0)
            throw std::invalid_argument("invalid positive integer");
        field = candidate; found = true;
    });
    return found;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Settings settings{8080, 2};
        check(set_option(settings, "port", "9000"), "known option rejected");
        check(!set_option(settings, "unknown", "1"), "unknown option accepted");
        bool rejected = false;
        try { set_option(settings, "workers", "2oops"); }
        catch (const std::invalid_argument&) { rejected = true; }
        check(rejected && settings.workers == 2, "invalid value changed config");
        std::cout << "port=" << settings.port << ", workers=" << settings.workers << '\n';
        std::cout << "OK 27-cli-configuration\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

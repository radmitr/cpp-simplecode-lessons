#include <nlohmann/json.hpp>
#include <cstdint>
#include "../common/reflection.hpp"

struct Settings { int port; int workers; };
nlohmann::json serialize(const Settings& value)
{
    nlohmann::json json;
    reflection_demo::for_each_field(value, [&](auto name, const auto& field) { json[std::string(name)] = field; });
    return json;
}
Settings parse_settings(std::string_view text)
{
    auto json = nlohmann::json::parse(text);
    if (!json.is_object() || json.size() != 2) throw std::invalid_argument("unexpected settings keys");
    Settings candidate{};
    reflection_demo::for_each_field(candidate, [&](auto name, auto& field) {
        const auto& value = json.at(std::string(name));
        if (!value.is_number_integer()) throw std::invalid_argument("integer setting expected");
        const auto number = value.get<std::int64_t>();
        if (number < 1 || number > 65535) throw std::invalid_argument("setting out of range");
        field = static_cast<int>(number);
    });
    if (candidate.workers > 64) throw std::invalid_argument("too many workers");
    return candidate;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Settings settings{8080, 2};
        const auto before = serialize(settings);
        bool rejected = false;
        try { settings = parse_settings(R"({"port":0,"workers":4})"); }
        catch (const std::exception&) { rejected = true; }
        check(rejected && serialize(settings) == before, "failed load changed settings");
        for (std::string_view bad : {R"([])", R"({})", R"({"port":1,"workers":2,"extra":3})",
             R"({"port":1.5,"workers":2})", R"({"port":"9000","workers":2})",
             R"({"port":18446744073709551615,"workers":2})", R"({"port":1,"workers":65})"})
        {
            bool invalid = false;
            try { (void)parse_settings(bad); }
            catch (const std::exception&) { invalid = true; }
            check(invalid, "invalid settings schema or range accepted");
        }
        settings = parse_settings(R"({"port":9000,"workers":4})");
        auto encoded = serialize(settings);
        check(parse_settings(encoded.dump()).port == 9000, "settings round trip failed");
        reflection_demo::for_each_field(settings, [](auto name, const auto& value) {
            std::cout << "--" << name << " (current " << value << ")\n";
        });
        std::cout << encoded.dump() << '\n';
        std::cout << "OK 29-settings-project\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

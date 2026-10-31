#include <nlohmann/json.hpp>
#include "../common/reflection.hpp"

struct Person { int id; std::string name; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Person person{7, "Ada"};
        nlohmann::json encoded;
        reflection_demo::for_each_field(person, [&](auto name, const auto& value) { encoded[std::string(name)] = value; });
        Person restored{};
        reflection_demo::for_each_field(restored, [&](auto name, auto& value) { encoded.at(std::string(name)).get_to(value); });
        check(restored.id == 7 && restored.name == "Ada", "JSON round trip failed");
        bool rejected = false;
        try { auto bad = encoded; bad["id"] = "oops"; bad.at("id").get_to(restored.id); }
        catch (const nlohmann::json::exception&) { rejected = true; }
        check(rejected, "wrong JSON type accepted");
        std::cout << encoded.dump() << '\n';
        std::cout << "OK 28-json-serialization\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

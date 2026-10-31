#include <nlohmann/json.hpp>
#include <string>
#include <cstdint>
#include "../common/check.hpp"

struct Config {std::string name; int count;};
Config parse_config(const nlohmann::json& document) {
    if(!document.is_object() || document.size()!=2 || !document.contains("name") || !document.contains("count"))
        throw std::invalid_argument("unexpected or missing keys");
    if(!document["name"].is_string() || !document["count"].is_number_integer())
        throw std::invalid_argument("wrong field type");
    const auto count=document["count"].get<std::int64_t>();
    if(count<0 || count>1000) throw std::invalid_argument("count out of range");
    return {document["name"].get<std::string>(),static_cast<int>(count)};
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        const auto document=nlohmann::json::parse(R"({"name":"Ada","count":3})");
        const auto config=parse_config(document);
        check(config.name=="Ada" && config.count==3,"JSON model mismatch");
        check(nlohmann::json::parse(document.dump())==document,"JSON syntax round trip failed");
        for(const auto& bad:{R"({"name":"Ada"})",R"({"name":4,"count":3})",R"({"name":"Ada","count":-1})",R"({"name":"Ada","count":3,"extra":true})"}) {
            bool rejected=false;
            try {(void)parse_config(nlohmann::json::parse(bad));} catch(const std::exception&) {rejected=true;}
            check(rejected,"invalid JSON model accepted");
        }
        std::cout << document.dump() << '\n';
        std::cout << "OK 15-json\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

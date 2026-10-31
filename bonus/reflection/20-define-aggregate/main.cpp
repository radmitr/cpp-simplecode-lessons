#include "../common/reflection.hpp"

struct Generated;
consteval {
    (void)std::meta::define_aggregate(^^Generated, {
        std::meta::data_member_spec(^^int, {.name = "id"}),
        std::meta::data_member_spec(^^double, {.name = "score"})
    });
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Generated object{7, 2.5};
        check(object.id == 7 && object.score == 2.5, "aggregate generation failed");
        reflection_demo::for_each_field(object, [](auto name, const auto& value) {
            std::cout << name << '=' << value << '\n';
        });
        std::cout << "OK 20-define-aggregate\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

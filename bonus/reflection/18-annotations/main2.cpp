#include "../common/reflection.hpp"

struct Label { char text[16]; };
struct Record { [[=Label{"identifier"}]] int id = 7; };

int main()
{
    constexpr auto annotations = std::define_static_array(
        std::meta::annotations_of_with_type(^^Record::id, ^^Label));
    static_assert(annotations.size() == 1);
    constexpr auto label = std::meta::extract<Label>(annotations[0]);
    check(std::string_view(label.text) == "identifier", "annotation value extraction failed");
    std::cout << label.text << "=7\nOK annotation-value\n";
}

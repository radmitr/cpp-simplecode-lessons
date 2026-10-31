#include <type_traits>
#include <utility>
#include "../common/check.hpp"

struct Item { int id; };
template<class T, class = void> struct has_id : std::false_type {};
template<class T> struct has_id<T, std::void_t<decltype(std::declval<T>().id)>> : std::true_type {};
template<class T> int read_id(const T& object)
{
    if constexpr (has_id<T>::value) return object.id;
    else return -1;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(std::is_same_v<decltype(Item::id), int>);
        static_assert(has_id<Item>::value);
        static_assert(!has_id<int>::value);
        Item object{9};
        check(read_id(object) == 9 && read_id(4) == -1, "detection failed");
        std::cout << "known expression detected; arbitrary field names unavailable\n";
        std::cout << "OK 04-traits-and-detection\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

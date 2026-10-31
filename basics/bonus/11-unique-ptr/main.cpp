#include <memory>
#include <utility>
#include "../common/check.hpp"

std::unique_ptr<int> make_number() { return std::make_unique<int>(7); }
void consume(std::unique_ptr<int> value) { check(*value == 7, "bad owned value"); }
struct Deleter { int* count; void operator()(int* p) const noexcept { ++*count; delete p; } };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        auto pointer = make_number();
        check(*pointer == 7, "factory failed");
        int* observed = pointer.get();
        check(observed == pointer.get(), "get must not transfer ownership");
        consume(std::move(pointer));
        check(!pointer, "owner should be empty");
        auto array = std::make_unique<int[]>(3);
        check(array[0] == 0, "array initialization failed");
        int deletions = 0;
        { std::unique_ptr<int, Deleter> traced(new int(9), Deleter{&deletions}); traced.reset(); }
        check(deletions == 1, "custom deleter called wrong number of times");
        std::cout << "exclusive ownership verified\n";
        std::cout << "OK 11-unique-ptr\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

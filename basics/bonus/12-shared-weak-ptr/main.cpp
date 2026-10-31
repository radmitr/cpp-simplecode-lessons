#include <memory>
#include "../common/check.hpp"

struct Node { std::shared_ptr<Node> child; std::weak_ptr<Node> parent; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        std::weak_ptr<Node> observed;
        {
            auto parent = std::make_shared<Node>();
            auto child = std::make_shared<Node>();
            parent->child = child;
            child->parent = parent;
            observed = parent;
            check(child->parent.lock() == parent, "weak parent lookup failed");
            check(parent.use_count() == 1, "weak pointer added an owner");
        }
        check(observed.expired() && !observed.lock(), "ownership cycle leaked parent");
        std::cout << "weak backlink breaks ownership cycle\n";
        std::cout << "OK 12-shared-weak-ptr\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

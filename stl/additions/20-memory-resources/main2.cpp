// C++17 — memory_resource, пул и выбор ресурса при копировании.
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory_resource>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

class CountingResource : public std::pmr::memory_resource
{
public:
    std::size_t bytes = 0;
    std::size_t allocations = 0;
private:
    void* do_allocate(std::size_t size, std::size_t alignment) override
    {
        void* memory = std::pmr::new_delete_resource()->allocate(size, alignment);
        bytes += size;
        ++allocations;
        return memory;
    }
    void do_deallocate(void* memory, std::size_t size, std::size_t alignment) override
    {
        std::pmr::new_delete_resource()->deallocate(memory, size, alignment);
        bytes -= size;
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override
    {
        return this == &other;
    }
};

int main()
{
    try
    {
        CountingResource upstream;
        {
            std::pmr::unsynchronized_pool_resource pool(&upstream);
            {
                std::pmr::vector<int> first(&pool);
                first.assign({1, 2, 3});
                std::pmr::vector<int> default_copy(first);
                std::pmr::vector<int> explicit_copy(first, &pool);
                std::pmr::vector<int> assigned(&upstream);
                assigned = first;
                check(default_copy.get_allocator().resource() == std::pmr::get_default_resource(), "copy selects default resource");
                check(explicit_copy.get_allocator().resource() == &pool, "explicit allocator");
                check(assigned.get_allocator().resource() == &upstream && assigned[2] == 3, "assignment preserves allocator");
                check(upstream.allocations > 0, "pool acquired blocks");
            }
            pool.release();
            check(upstream.bytes == 0, "release after containers are gone");
        }
        check(upstream.bytes == 0, "resource cleanup");
        std::cout << "all blocks released\n";
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

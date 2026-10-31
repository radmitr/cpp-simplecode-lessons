#include <exception>
#include <future>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>

int main()
{
    std::promise<int> promise;
    std::shared_future<int> result = promise.get_future().share();
    std::mutex outputMtx;
    int errors = 0;

    auto worker = [result, &outputMtx, &errors](int id) {
        try
        {
            result.get();
        }
        catch (const std::runtime_error& error)
        {
            std::lock_guard<std::mutex> guard(outputMtx);
            ++errors;
            std::cout << "Worker " << id << ": " << error.what() << '\n';
        }
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    promise.set_exception(
        std::make_exception_ptr(std::runtime_error("Configuration unavailable")));

    t1.join();
    t2.join();
    t3.join();
    std::cout << "Workers that received the exception: " << errors << '\n';
    return errors == 3 ? 0 : 1;
}

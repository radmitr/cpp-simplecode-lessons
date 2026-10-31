#include <iostream>
#include <mutex>
#include <string>
#include <thread>

int main()
{
    std::once_flag initFlag;
    std::string settings;
    int initializationCount = 0;
    std::mutex outputMtx;

    auto initialize = [&]() {
        settings = "server=localhost";
        ++initializationCount;
    };

    auto worker = [&](int id) {
        // С одним initFlag функция успешно выполнится только один раз.
        // Остальные вызовы дождутся её завершения и увидят готовые settings.
        std::call_once(initFlag, initialize);

        std::lock_guard<std::mutex> guard(outputMtx);
        std::cout << "Worker " << id << ": " << settings << '\n';
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    t1.join();
    t2.join();
    t3.join();

    std::cout << "Successful initializations: " << initializationCount << '\n';
    return initializationCount == 1 && settings == "server=localhost" ? 0 : 1;
}

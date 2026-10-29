#ifndef BONUS_THREAD_POOL_HPP
#define BONUS_THREAD_POOL_HPP

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

// Учебный пул: принимает функции без аргументов, возвращающие int.
class ThreadPool
{
public:
    explicit ThreadPool(std::size_t count)
    {
        if (count == 0)
        {
            throw std::invalid_argument("Thread count must be positive");
        }
        workers.reserve(count);
        try
        {
            for (std::size_t i = 0; i < count; ++i)
            {
                workers.emplace_back([this]() { work(); });
            }
        }
        catch (...)
        {
            // Если создание одного потока не удалось, завершаем уже созданные.
            finish();
            throw;
        }
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    ~ThreadPool()
    {
        finish();
    }

    std::future<int> submit(std::function<int()> function)
    {
        // packaged_task сохраняет результат или исключение в связанном future.
        auto task = std::make_shared<std::packaged_task<int()>>(std::move(function));
        std::future<int> result = task->get_future();
        {
            std::lock_guard<std::mutex> guard(mtx);
            if (stopping)
            {
                throw std::runtime_error("Pool is stopping");
            }
            // std::function требует копируемый объект: захватываем shared_ptr.
            tasks.emplace([task]() { (*task)(); });
        }
        cv.notify_one();
        return result;
    }

private:
    void work()
    {
        for (;;)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this]() { return stopping || !tasks.empty(); });
                if (stopping && tasks.empty())
                {
                    return;
                }
                task = std::move(tasks.front());
                tasks.pop();
            }
            task(); // Выполняем без удержания мьютекса очереди.
        }
    }

    void finish()
    {
        {
            std::lock_guard<std::mutex> guard(mtx);
            stopping = true;
        }
        cv.notify_all();
        for (std::thread& worker : workers)
        {
            worker.join();
        }
    }

    std::mutex mtx;
    std::condition_variable cv;
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> workers;
    bool stopping = false;
};

#endif

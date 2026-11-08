// C++26 — std::execution senders/receivers (зависит от реализации).
#include <exception>
#include <execution>
#include <iostream>
#include <tuple>
#include <utility>
#include <version>

#include "../common.hpp"

#if CPP_EXECUTION_AVAILABLE

#include "../../../basics/additions/common/check.hpp"

// Объявляем оба допустимых канала: значение и остановку.
struct MaybeValue
{
    using sender_concept = execution_demo::ex::sender_tag;
    using completion_signatures = execution_demo::ex::completion_signatures<
        execution_demo::ex::set_value_t(int), execution_demo::ex::set_stopped_t()>;
    // Функция для актуального протокола; alias выше — для ранних реализаций.
    template<class Self, class... Env>
    static consteval completion_signatures get_completion_signatures() noexcept
    {
        return {};
    }
    bool stopped;
    template<class Receiver> struct Operation
    {
        using operation_state_concept = execution_demo::ex::operation_state_tag;
        bool stopped;
        Receiver receiver;
        void start() & noexcept
        {
            if (stopped) execution_demo::ex::set_stopped(std::move(receiver));
            else execution_demo::ex::set_value(std::move(receiver), 7);
        }
    };
    template<class Receiver> auto connect(Receiver receiver) const
    {
        return Operation<Receiver>{stopped, std::move(receiver)};
    }
};

int main()
{
    try
    {
        int calls = 0;
        auto work = execution_demo::ex::just(3) | execution_demo::ex::then([&](int x) { ++calls; return x * 2; });
        check(calls == 0, "lazy description");
        auto result = execution_demo::sync_wait(work);
        check(result && std::get<0>(*result) == 6 && calls == 1, "start and wait");
        auto stopped = execution_demo::sync_wait(MaybeValue{true});
        check(!stopped, "stopped completion");
        auto completed = execution_demo::sync_wait(MaybeValue{false});
        check(completed && std::get<0>(*completed) == 7, "value completion");
        std::cout << std::get<0>(*result) << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
#else
int main()
{
    std::cout << "UNAVAILABLE: additions/execution/01-senders\n";
    return 77;
}
#endif

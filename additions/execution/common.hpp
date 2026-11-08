// C++26 — стандартные senders; C++20 — внешний профиль NVIDIA stdexec.
#pragma once
#include <execution>
#include <utility>
#include <version>

#if defined(CPP_USE_STDEXEC)
#include <stdexec/execution.hpp>
#define CPP_EXECUTION_AVAILABLE 1
namespace execution_demo
{
namespace ex = stdexec;
using stdexec::sync_wait;
}
#elif defined(__cpp_lib_execution) && __cpp_lib_execution >= 202406L
#define CPP_EXECUTION_AVAILABLE 1
namespace execution_demo
{
namespace ex = std::execution;
using std::this_thread::sync_wait;
}
#else
#define CPP_EXECUTION_AVAILABLE 0
#endif

#if CPP_EXECUTION_AVAILABLE
namespace execution_demo
{
// Оба канала объявлены в типе, даже когда конкретный запуск выбирает остановку.
struct MaybeValue
{
    using sender_concept = ex::sender_tag;
    using completion_signatures = ex::completion_signatures<ex::set_value_t(int), ex::set_stopped_t()>;
    template<class Self, class... Env>
    static consteval completion_signatures get_completion_signatures() noexcept { return {}; }
    bool stopped;
    int value;
    template<class Receiver> struct Operation
    {
        using operation_state_concept = ex::operation_state_tag;
        bool stopped;
        int value;
        Receiver receiver;
        void start() & noexcept
        {
            if (stopped) ex::set_stopped(std::move(receiver));
            else ex::set_value(std::move(receiver), value);
        }
    };
    template<class Receiver> auto connect(Receiver receiver) const
    {
        return Operation<Receiver>{stopped, value, std::move(receiver)};
    }
};
}
#endif

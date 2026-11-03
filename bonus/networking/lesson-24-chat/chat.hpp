// C++11 — std::shared_ptr, std::thread, std::function и лямбды.
// C++14 — захват лямбды с инициализацией.
// C++17 — std::string_view, std::from_chars и inline-переменные.
#ifndef NETWORKING_CHAT_HPP
#define NETWORKING_CHAT_HPP

#include "../common/boost_net.hpp"
#include "../../../common/console.hpp"
#include <deque>
#include <exception>
#include <functional>
#include <thread>

namespace chat
{
namespace asio = boost::asio;
using Tcp = asio::ip::tcp;
using Error = boost::system::error_code;
using Milliseconds = std::chrono::milliseconds;
inline constexpr std::size_t maxMessage = 1024;

inline void report(const std::string& text)
{
    std::cout << text << std::endl;
}

inline bool validName(std::string_view name)
{
    return !name.empty() && name.size() <= 16 && std::all_of(name.begin(), name.end(),
        [](unsigned char ch) {
            return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
                || (ch >= '0' && ch <= '9') || ch == '_' || ch == '-';
        });
}

inline bool validText(std::string_view text)
{
    return !text.empty() && text.size() <= maxMessage
        && std::all_of(text.begin(), text.end(), [](unsigned char ch) {
            return ch >= 32 && ch != 127;
        });
}

inline bool validSequence(std::string_view text)
{
    std::uint64_t value = 0;
    const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
    return result.ec == std::errc{} && result.ptr == text.data() + text.size()
        && value != 0 && std::to_string(value) == text;
}

// Один объект обслуживает ровно одно TCP-соединение, даже после переподключения.
class Channel : public std::enable_shared_from_this<Channel>
{
public:
    explicit Channel(Tcp::socket socket)
        : socket_(std::move(socket)), writeTimer_(socket_.get_executor()) {}

    Tcp::socket& socket() { return socket_; }

    void start(std::function<void(std::string)> onLine,
               std::function<void(std::string)> onClose)
    {
        onLine_ = std::move(onLine);
        onClose_ = std::move(onClose);
        read();
    }

    void send(std::string line)
    {
        if (closed_) return;
        if (output_.size() == 64) return close("переполнена очередь отправки");
        const bool idle = output_.empty();
        output_.push_back(std::make_shared<const std::string>(std::move(line)));
        if (idle) write();
    }

    void close(std::string reason)
    {
        if (closed_) return;
        closed_ = true;
        writeTimer_.cancel();
        Error ignored;
        socket_.shutdown(Tcp::socket::shutdown_both, ignored);
        socket_.close(ignored);
        output_.clear();
        onLine_ = {};
        auto notify = std::move(onClose_); // Разрываем цикл Channel -> callback -> Session.
        if (notify) notify(std::move(reason));
    }

private:
    void read()
    {
        asio::async_read_until(socket_, input_, '\n',
            [self = shared_from_this()](Error error, std::size_t) {
                if (self->closed_) return;
                if (error) return self->close("чтение: " + error.message());
                std::istream input(&self->input_);
                std::string line;
                std::getline(input, line);
                // Копия обработчика остаётся жива, даже если он закроет Channel.
                auto notify = self->onLine_;
                notify(std::move(line));
                if (!self->closed_) self->read();
            });
    }

    void write()
    {
        const auto message = output_.front();
        const auto operation = ++writeOperation_;
        writeTimer_.expires_after(Milliseconds(3000));
        writeTimer_.async_wait([self = shared_from_this(), operation](Error error) {
            if (!error && !self->closed_ && operation == self->writeOperation_)
                self->close("таймаут отправки");
        });
        // message сохраняет память до завершения записи, в том числе после close().
        asio::async_write(socket_, asio::buffer(*message),
            [self = shared_from_this(), message](Error error, std::size_t) {
                if (self->closed_) return;
                ++self->writeOperation_;
                self->writeTimer_.cancel();
                if (error) return self->close("запись: " + error.message());
                self->output_.pop_front();
                if (!self->output_.empty()) self->write();
            });
    }

    Tcp::socket socket_;
    asio::steady_timer writeTimer_;
    asio::streambuf input_{4096};
    std::deque<std::shared_ptr<const std::string>> output_;
    std::function<void(std::string)> onLine_;
    std::function<void(std::string)> onClose_;
    std::uint64_t writeOperation_ = 0;
    bool closed_ = false;
};

// Главный поток читает консоль; только worker обращается к сетевым объектам.
template <typename Input, typename Stop>
void runConsole(asio::io_context& io, Input onInput, Stop onStop)
{
    auto work = asio::make_work_guard(io);
    std::exception_ptr networkError;
    std::thread worker([&]() {
        try { io.run(); }
        catch (...)
        {
            networkError = std::current_exception();
            std::cerr << "Сетевая ошибка: введите /quit для завершения." << std::endl;
        }
    });
    auto finish = [&]() {
        asio::post(io, [&]() {
            onStop();
            work.reset();
        });
        worker.join();
        if (networkError)
        {
            onStop(); // io.run() уже завершился; сетевые объекты можно закрыть здесь.
            work.reset();
        }
    };
    try
    {
        std::string line;
        while (std::getline(std::cin, line) && line != "/quit")
            asio::post(io, [onInput, line]() { onInput(line); });
    }
    catch (...)
    {
        finish();
        throw;
    }
    finish();
    if (networkError) std::rethrow_exception(networkError);
}
} // namespace chat
#endif

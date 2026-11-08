// C++11 — std::shared_ptr, std::chrono, std::thread и лямбды.
// C++14 — захват лямбды с инициализацией; ввод-вывод предоставляет Boost.Asio.
#include <algorithm>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include "chat.hpp"

using namespace chat;

class Client
{
public:
    Client(asio::io_context& io, std::uint16_t port, std::string name)
        : io_(io), endpoint_(asio::ip::address_v4::loopback(), port),
          timer_(io), heartbeat_(io), name_(std::move(name)) {}

    void connect()
    {
        if (stopped_) return;
        auto channel = std::make_shared<Channel>(Tcp::socket(io_));
        current_ = channel;
        report("Подключение...");
        timer_.expires_after(Milliseconds(2000));
        timer_.async_wait([this, channel](Error error) {
            if (!error && current_ == channel && !ready_)
                lost(channel, "таймаут подключения или READY");
        });
        channel->socket().async_connect(endpoint_, [this, channel](Error error) {
            if (current_ != channel || stopped_) return;
            if (error) return lost(channel, "connect: " + error.message());
            channel->start([this, weak = std::weak_ptr<Channel>(channel)](std::string line) {
                    if (auto active = weak.lock()) receive(active, line);
                },
                [this, weak = std::weak_ptr<Channel>(channel)](std::string reason) {
                    if (auto active = weak.lock()) lost(active, reason);
                });
            channel->send("HELLO " + name_ + '\n');
        });
    }

    void send(const std::string& text)
    {
        if (!validText(text))
            return report("Введите 1–1024 байта текста без управляющих символов.");
        if (!ready_)
            return report("Нет соединения: сообщение не отправлено и не сохранено.");
        current_->send("MSG " + text + '\n');
    }

    void stop()
    {
        if (stopped_) return;
        stopped_ = true;
        ready_ = false;
        timer_.cancel();
        heartbeat_.cancel();
        auto channel = std::move(current_);
        if (channel) channel->close("выход из чата");
        report("Клиент остановлен.");
    }

private:
    void lost(const std::shared_ptr<Channel>& channel, const std::string& reason)
    {
        if (stopped_ || current_ != channel) return;
        current_.reset(); // Старые обработчики больше не относятся к новому соединению.
        ready_ = false;
        awaitingPong_ = false;
        timer_.cancel();
        heartbeat_.cancel();
        channel->close(reason);
        report("Связь потеряна: " + reason);
        report("Повтор через " + std::to_string(backoff_.count()) + " мс.");
        timer_.expires_after(backoff_);
        backoff_ = std::min(backoff_ * 2, Milliseconds(2000));
        timer_.async_wait([this](Error error) { if (!error && !stopped_) connect(); });
    }

    void receive(const std::shared_ptr<Channel>& channel, const std::string& line)
    {
        if (current_ != channel || stopped_) return;
        if (!ready_)
        {
            if (line != "READY " + name_) return lost(channel, "неверный READY");
            ready_ = true;
            timer_.cancel();
            backoff_ = Milliseconds(100);
            sequence_ = 0;
            report("Подключено: " + name_);
            return ping();
        }
        if (line.compare(0, 5, "PONG ") == 0)
        {
            if (!awaitingPong_ || line != "PONG " + std::to_string(sequence_))
                return lost(channel, "неверный номер PONG");
            awaitingPong_ = false;
            heartbeat_.cancel();
            heartbeat_.expires_after(Milliseconds(1000));
            heartbeat_.async_wait([this, channel](Error error) {
                if (!error && current_ == channel && !stopped_) ping();
            });
        }
        else if (line.compare(0, 5, "CHAT ") == 0)
        {
            const auto separator = line.find(' ', 5);
            if (separator == std::string::npos || !validName(line.substr(5, separator - 5))
                || !validText(line.substr(separator + 1)))
                return lost(channel, "неверное сообщение CHAT");
            report(line.substr(5, separator - 5) + ": " + line.substr(separator + 1));
        }
        else
            lost(channel, "неизвестная команда сервера");
    }

    void ping()
    {
        auto channel = current_;
        const auto sequence = ++sequence_;
        awaitingPong_ = true;
        channel->send("PING " + std::to_string(sequence) + '\n');
        if (current_ != channel) return;
        heartbeat_.expires_after(Milliseconds(1500));
        heartbeat_.async_wait([this, channel, sequence](Error error) {
            if (!error && current_ == channel && awaitingPong_ && sequence == sequence_)
                lost(channel, "heartbeat: PONG не получен за 1500 мс");
        });
    }

    asio::io_context& io_;
    Tcp::endpoint endpoint_;
    asio::steady_timer timer_;
    asio::steady_timer heartbeat_;
    std::string name_;
    std::shared_ptr<Channel> current_;
    Milliseconds backoff_{100};
    std::uint64_t sequence_ = 0;
    bool ready_ = false;
    bool awaitingPong_ = false;
    bool stopped_ = false;
};

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        if (argc > 3) throw std::runtime_error("Использование: client [port] [name]");
        const auto port = argc >= 2 ? net::parsePort(argv[1]) : 42024;
        const std::string name = argc == 3 ? argv[2] : "guest";
        if (!validName(name))
            throw std::runtime_error("Имя: 1–16 символов A–Z, a–z, 0–9, _ или -");
        asio::io_context io;
        Client client(io, port, name);
        report("Введите сообщение или /quit. Переподключение продолжается до выхода.");
        client.connect();
        runConsole(io, [&](const std::string& line) { client.send(line); },
                   [&]() { client.stop(); });
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}

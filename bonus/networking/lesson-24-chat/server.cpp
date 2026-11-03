// C++11 — std::shared_ptr, std::enable_shared_from_this, std::chrono и лямбды.
// C++14 — захват лямбды с инициализацией; ввод-вывод предоставляет Boost.Asio.
#include "chat.hpp"
#include <set>
#include <vector>

using namespace chat;

class Room;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(Tcp::socket socket, Room& room)
        : channel_(std::make_shared<Channel>(std::move(socket))),
          idleTimer_(channel_->socket().get_executor()), room_(room) {}

    void start();
    void stop() { channel_->close("остановка сервера"); }
    void deliver(const std::string& line) { if (!name_.empty()) channel_->send(line); }

private:
    void receive(const std::string& line);
    void armIdleTimer();
    std::shared_ptr<Channel> channel_;
    asio::steady_timer idleTimer_;
    Room& room_;
    std::string name_;
    std::uint64_t idleOperation_ = 0;
    bool closed_ = false;
};

class Room
{
public:
    Room(asio::io_context& io, std::uint16_t port) : listener_(io)
    {
        const Tcp::endpoint endpoint(asio::ip::address_v4::loopback(), port);
        listener_.open(endpoint.protocol());
        listener_.set_option(Tcp::acceptor::reuse_address(true));
        listener_.bind(endpoint);
        listener_.listen();
    }

    void start()
    {
        report("Listening on 127.0.0.1:" + std::to_string(listener_.local_endpoint().port()));
        report("Введите /quit для остановки сервера.");
        accept();
    }

    void broadcast(const std::string& line)
    {
        // send() может закрыть медленного клиента и удалить его из sessions_.
        const std::vector<std::shared_ptr<Session>> recipients(sessions_.begin(), sessions_.end());
        for (const auto& session : recipients) session->deliver(line);
    }

    void remove(const std::shared_ptr<Session>& session) { sessions_.erase(session); }
    bool failed() const { return failed_; }

    void stop()
    {
        if (stopped_) return;
        stopped_ = true;
        Error ignored;
        listener_.close(ignored);
        const auto remaining = sessions_;
        for (const auto& session : remaining) session->stop();
        report("Сервер остановлен.");
    }

private:
    void accept()
    {
        listener_.async_accept([this](Error error, Tcp::socket socket) {
            if (stopped_) return;
            if (error)
            {
                failed_ = true;
                report("Ошибка accept: " + error.message());
                return stop();
            }
            if (sessions_.size() < 16)
            {
                auto session = std::make_shared<Session>(std::move(socket), *this);
                sessions_.insert(session);
                session->start();
            }
            else
                report("Достигнут предел: 16 соединений.");
            accept();
        });
    }

    Tcp::acceptor listener_;
    std::set<std::shared_ptr<Session>> sessions_;
    bool stopped_ = false;
    bool failed_ = false;
};

void Session::start()
{
    channel_->start([self = shared_from_this()](std::string line) { self->receive(line); },
        [self = shared_from_this()](std::string reason) {
            self->closed_ = true;
            self->idleTimer_.cancel();
            self->room_.remove(self);
            report("Клиент " + (self->name_.empty() ? "без имени" : self->name_)
                + " отключён: " + reason);
        });
    armIdleTimer();
}

void Session::armIdleTimer()
{
    if (closed_) return;
    const auto operation = ++idleOperation_;
    idleTimer_.expires_after(Milliseconds(5000));
    idleTimer_.async_wait([self = shared_from_this(), operation](Error error) {
        if (!error && operation == self->idleOperation_)
            self->channel_->close("клиент молчит более 5 секунд");
    });
}

void Session::receive(const std::string& line)
{
    if (name_.empty())
    {
        if (line.compare(0, 6, "HELLO ") != 0 || !validName(line.substr(6)))
            return channel_->close("ожидалось HELLO и имя из 1–16 ASCII-символов");
        name_ = line.substr(6);
        channel_->send("READY " + name_ + '\n');
        report("В чате: " + name_);
    }
    else if (line.compare(0, 5, "PING ") == 0 && validSequence(line.substr(5)))
        channel_->send("PONG " + line.substr(5) + '\n');
    else if (line.compare(0, 4, "MSG ") == 0 && validText(line.substr(4)))
        room_.broadcast("CHAT " + name_ + ' ' + line.substr(4) + '\n');
    else
        return channel_->close("неверная команда или слишком длинное сообщение");
    armIdleTimer();
}

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        asio::io_context io;
        Room room(io, net::portArgument(argc, argv, 42024, true));
        room.start();
        runConsole(io, [](const std::string&) { report("Команда сервера: /quit"); },
                   [&]() { room.stop(); });
        return room.failed() ? 1 : 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}

#include "../common/boost_net.hpp"
#include <functional>
#include <istream>

namespace asio = boost::asio;
using Tcp = asio::ip::tcp;
using Error = boost::system::error_code;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(Tcp::socket socket, bool& failed)
        : socket_(std::move(socket)), timer_(socket_.get_executor()), failed_(failed) {}

    void start()
    {
        timer_.expires_after(std::chrono::seconds(3));
        timer_.async_wait([self = shared_from_this()](Error error) {
            if (!error) self->finish(asio::error::timed_out);
        });
        asio::async_read_until(socket_, input_, '\n',
            [self = shared_from_this()](Error error, std::size_t) {
                if (error) return self->finish(error);
                std::istream input(&self->input_);
                std::getline(input, self->reply_);
                self->reply_ += '\n';
                // reply_ — поле объекта, оно переживает async_write().
                asio::async_write(self->socket_, asio::buffer(self->reply_),
                    [self](Error writeError, std::size_t) { self->finish(writeError); });
            });
    }

private:
    void finish(Error error)
    {
        if (finished_) return;
        finished_ = true;
        timer_.cancel();
        Error ignored;
        socket_.close(ignored);
        if (error)
        {
            failed_ = true;
            std::cerr << "Session: " << error.message() << '\n';
        }
        else
            std::cout << "Async handled: " << reply_;
    }
    Tcp::socket socket_;
    asio::steady_timer timer_;
    asio::streambuf input_{4096};
    std::string reply_;
    bool& failed_;
    bool finished_ = false;
};

int main(int argc, char* argv[])
{
    try
    {
        asio::io_context io;
        Tcp::acceptor listener(io, {asio::ip::address_v4::loopback(),
                                    net::portArgument(argc, argv, 42018, true)});
        std::cout << "Listening on 127.0.0.1:" << listener.local_endpoint().port() << std::endl;
        bool failed = false;
        int accepted = 0;
        asio::steady_timer acceptTimer(io, std::chrono::seconds(15));
        acceptTimer.async_wait([&](Error error) {
            if (!error)
            {
                failed = true;
                Error ignored;
                listener.close(ignored);
            }
        });
        std::function<void()> acceptNext;
        acceptNext = [&]() {
            listener.async_accept([&](Error error, Tcp::socket socket) {
                if (error)
                {
                    failed = true;
                    acceptTimer.cancel();
                    return;
                }
                ++accepted;
                std::make_shared<Session>(std::move(socket), failed)->start();
                if (accepted < 3) acceptNext();
                else
                {
                    acceptTimer.cancel();
                    Error ignored;
                    listener.close(ignored);
                }
            });
        };
        acceptNext();
        io.run(); // Один поток вызывает готовые обработчики всех трёх соединений.
        std::cout << "Async clients: " << accepted << '\n';
        return !failed && accepted == 3 ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

// C++11 — std::thread, std::atomic, std::mutex и std::shared_ptr.
// C++14 — захват лямбды с инициализацией; strand предоставляет Boost.Asio.
#include "../common/boost_net.hpp"
#include "../../../common/console.hpp"
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

namespace asio = boost::asio;
using Tcp = asio::ip::tcp;
using Error = boost::system::error_code;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(asio::io_context& io, Tcp::socket socket, std::atomic<int>& completed,
            std::atomic<bool>& failed)
        : strand_(asio::make_strand(io)), socket_(std::move(socket)), timer_(io),
          completed_(completed), failed_(failed) {}

    void start()
    {
        asio::dispatch(strand_, [self = shared_from_this()]() { self->read(); });
    }

private:
    void read()
    {
        // И таймер, и чтение используют поля сессии через один strand.
        const auto operation = ++readOperation_;
        timer_.expires_after(std::chrono::seconds(3));
        timer_.async_wait(asio::bind_executor(strand_,
            [self = shared_from_this(), operation](Error error) {
                if (!error && operation == self->readOperation_) self->finish(true);
            }));
        asio::async_read_until(socket_, input_, '\n', asio::bind_executor(strand_,
            [self = shared_from_this()](Error error, std::size_t) {
                if (self->finished_) return;
                if (error) return self->finish(true);
                std::istream input(&self->input_);
                std::string line;
                std::getline(input, line);
                self->reply_ = std::to_string(++self->sequence_) + ":" + line + '\n';
                asio::async_write(self->socket_, asio::buffer(self->reply_),
                    asio::bind_executor(self->strand_, [self](Error writeError, std::size_t) {
                        if (self->finished_) return;
                        self->timer_.cancel();
                        if (writeError) return self->finish(true);
                        if (self->sequence_ == 3) self->finish(false);
                        else self->read();
                    }));
            }));
    }

    void finish(bool error)
    {
        if (finished_) return;
        finished_ = true;
        timer_.cancel();
        Error ignored;
        socket_.close(ignored);
        if (error) failed_ = true;
        else ++completed_;
    }

    asio::strand<asio::io_context::executor_type> strand_;
    Tcp::socket socket_;
    asio::steady_timer timer_;
    asio::streambuf input_{4096};
    std::string reply_;
    int sequence_ = 0;
    std::uint64_t readOperation_ = 0;
    bool finished_ = false;
    std::atomic<int>& completed_;
    std::atomic<bool>& failed_;
};

void runPool(asio::io_context& io)
{
    std::vector<std::thread> workers;
    std::mutex errorMutex;
    std::exception_ptr failure;
    auto run = [&]() {
        try { io.run(); }
        catch (...)
        {
            std::lock_guard<std::mutex> lock(errorMutex);
            if (!failure) failure = std::current_exception();
            io.stop();
        }
    };
    try
    {
        for (int i = 0; i < 2; ++i) workers.emplace_back(run);
        run(); // Всего три потока вызывают run(), включая главный.
    }
    catch (...)
    {
        io.stop();
        for (auto& worker : workers) worker.join();
        throw;
    }
    for (auto& worker : workers) worker.join();
    if (failure) std::rethrow_exception(failure);
}

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        asio::io_context io;
        auto control = asio::make_strand(io);
        Tcp::acceptor listener(control, {asio::ip::address_v4::loopback(),
                                        net::portArgument(argc, argv, 42021, true)});
        asio::steady_timer acceptTimer(control, std::chrono::seconds(15));
        std::atomic<bool> failed{false};
        std::atomic<int> completed{0};
        int accepted = 0;
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
                if (error) { failed = true; acceptTimer.cancel(); return; }
                std::make_shared<Session>(io, std::move(socket), completed, failed)->start();
                if (++accepted < 3) acceptNext();
                else
                {
                    acceptTimer.cancel();
                    Error ignored;
                    listener.close(ignored);
                }
            });
        };
        std::cout << "Listening on 127.0.0.1:" << listener.local_endpoint().port() << std::endl;
        // Начальная постановка accept выполняется до запуска пула.
        acceptNext();
        runPool(io);
        std::cout << "Strand clients: " << completed << "; run threads: 3\n";
        return !failed && completed == 3 ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}

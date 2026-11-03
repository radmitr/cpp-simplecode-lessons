// C++11 — std::make_shared, std::move, std::chrono, std::to_string.
// C++14 — захват лямбды с инициализацией.
#include <string>
#include <utility>
#include <cstddef>
#include "../common/boost_net.hpp"
#include "../../../common/console.hpp"
#include <boost/asio/ssl.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace ssl = asio::ssl;
namespace websocket = beast::websocket;
using Tcp = asio::ip::tcp;
using Error = boost::system::error_code;

class WebSocketSession : public std::enable_shared_from_this<WebSocketSession>
{
public:
    WebSocketSession(Tcp::socket socket, ssl::context& tls, bool& failed)
        : stream_(std::move(socket), tls), timer_(stream_.get_executor()),
          overall_(stream_.get_executor()), failed_(failed) {}

    void start()
    {
        stream_.read_message_max(4096);
        auto options = websocket::stream_base::timeout::suggested(beast::role_type::server);
        options.handshake_timeout = std::chrono::seconds(2);
        options.idle_timeout = std::chrono::seconds(2);
        options.keep_alive_pings = false;
        stream_.set_option(options);
        overall_.expires_after(std::chrono::seconds(5));
        overall_.async_wait([self = shared_from_this()](Error error) {
            if (!error) self->finish(asio::error::timed_out);
        });
        stream_.next_layer().async_handshake(ssl::stream_base::server,
            [self = shared_from_this()](Error error) {
            if (error) return self->finish(error);
            self->stream_.async_accept([self](Error upgradeError) {
                if (upgradeError) return self->finish(upgradeError);
                self->stream_.text(true);
                self->sendNext();
            });
        });
    }

private:
    void sendNext()
    {
        timer_.expires_after(std::chrono::milliseconds(100));
        timer_.async_wait([self = shared_from_this()](Error error) {
            if (error) return;
            self->message_ = "tick " + std::to_string(++self->sequence_);
            self->stream_.async_write(asio::buffer(self->message_),
                [self](Error writeError, std::size_t) {
                    if (writeError) return self->finish(writeError);
                    if (self->sequence_ < 3) self->sendNext();
                    else self->receiveAck();
                });
        });
    }
    void receiveAck()
    {
        stream_.async_read(input_, [self = shared_from_this()](Error error, std::size_t) {
            if (error) return self->finish(error);
            if (!self->stream_.got_text() || beast::buffers_to_string(self->input_.data()) != "ACK 3")
                return self->finish(asio::error::invalid_argument);
            self->stream_.async_close(websocket::close_code::normal,
                [self](Error closeError) { self->finish(closeError); });
        });
    }
    void finish(Error error)
    {
        if (finished_) return;
        finished_ = true;
        timer_.cancel();
        overall_.cancel();
        Error ignored;
        beast::get_lowest_layer(stream_).close(ignored);
        if (error)
        {
            failed_ = true;
            std::cerr << "WebSocket: " << error.message() << '\n';
        }
        else std::cout << "WSS completed: ACK 3\n";
    }
    websocket::stream<beast::ssl_stream<Tcp::socket>> stream_;
    asio::steady_timer timer_;
    asio::steady_timer overall_;
    beast::flat_buffer input_;
    std::string message_;
    int sequence_ = 0;
    bool& failed_;
    bool finished_ = false;
};

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        asio::io_context io;
        if (argc != 4) throw std::runtime_error("Использование: server port certificate.pem key.pem");
        ssl::context tls(ssl::context::tls_server);
        if (!SSL_CTX_set_min_proto_version(tls.native_handle(), TLS1_2_VERSION))
            throw std::runtime_error("Не удалось ограничить версию TLS");
        tls.use_certificate_chain_file(argv[2]);
        tls.use_private_key_file(argv[3], ssl::context::pem);
        Tcp::acceptor listener(io, {asio::ip::address_v4::loopback(),
                                    net::parsePort(argv[1], true)});
        std::cout << "Listening on 127.0.0.1:" << listener.local_endpoint().port() << std::endl;
        bool failed = false;
        asio::steady_timer timer(io, std::chrono::seconds(15));
        timer.async_wait([&](Error error) {
            if (!error)
            {
                failed = true;
                Error ignored;
                listener.close(ignored);
            }
        });
        listener.async_accept([&](Error error, Tcp::socket socket) {
            timer.cancel();
            if (error) { failed = true; return; }
            std::make_shared<WebSocketSession>(std::move(socket), tls, failed)->start();
        });
        io.run();
        return failed ? 1 : 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

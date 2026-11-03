// C++11 — std::make_shared, std::chrono, std::to_string, auto.
// C++14 — захват лямбды с инициализацией.
#include <string>
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

class WebSocketClient : public std::enable_shared_from_this<WebSocketClient>
{
public:
    WebSocketClient(asio::io_context& io, ssl::context& tls, bool& failed)
        : stream_(io, tls), timer_(io), failed_(failed) {}
    void start(std::uint16_t port, const std::string& host)
    {
        stream_.next_layer().set_verify_mode(ssl::verify_peer);
        stream_.next_layer().set_verify_callback(ssl::host_name_verification(host));
        if (!SSL_set_tlsext_host_name(stream_.next_layer().native_handle(), host.c_str()))
            throw std::runtime_error("Не удалось установить TLS SNI");
        stream_.read_message_max(4096);
        stream_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));
        timer_.expires_after(std::chrono::seconds(5));
        timer_.async_wait([self = shared_from_this()](Error error) {
            if (!error) self->finish(asio::error::timed_out);
        });
        beast::get_lowest_layer(stream_).async_connect({asio::ip::address_v4::loopback(), port},
            [self = shared_from_this(), port, host](Error error) {
                if (error) return self->finish(error);
                self->stream_.next_layer().async_handshake(ssl::stream_base::client,
                    [self, port, host](Error tlsError) {
                    if (tlsError) return self->finish(tlsError);
                    self->stream_.async_handshake(host + ":" + std::to_string(port), "/events",
                    [self](Error handshakeError) {
                        if (handshakeError) return self->finish(handshakeError);
                        self->readEvent();
                    });
                });
            });
    }
private:
    void readEvent()
    {
        input_.consume(input_.size());
        stream_.async_read(input_, [self = shared_from_this()](Error error, std::size_t) {
            if (error) return self->finish(error);
            const auto message = beast::buffers_to_string(self->input_.data());
            if (!self->stream_.got_text() || message != "tick " + std::to_string(++self->received_))
                return self->finish(asio::error::invalid_argument);
            std::cout << "Event: " << message << '\n';
            if (self->received_ < 3) return self->readEvent();
            self->stream_.text(true);
            self->stream_.async_write(asio::buffer(self->ack_),
                [self](Error writeError, std::size_t) {
                    if (writeError) return self->finish(writeError);
                    self->input_.consume(self->input_.size());
                    self->stream_.async_read(self->input_, [self](Error closeError, std::size_t) {
                        if (closeError != websocket::error::closed)
                            return self->finish(closeError ? closeError : Error(asio::error::fault));
                        self->finish({}); // Beast уже выполнил TLS teardown.
                    });
                });
        });
    }
    void finish(Error error)
    {
        if (finished_) return;
        finished_ = true;
        timer_.cancel();
        Error ignored;
        beast::get_lowest_layer(stream_).close(ignored);
        if (error)
        {
            failed_ = true;
            std::cerr << "WebSocket client: " << error.message() << '\n';
        }
        else std::cout << "WSS complete: " << received_ << " events\n";
    }
    websocket::stream<beast::ssl_stream<Tcp::socket>> stream_;
    asio::steady_timer timer_;
    beast::flat_buffer input_;
    const std::string ack_ = "ACK 3";
    int received_ = 0;
    bool& failed_;
    bool finished_ = false;
};

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        asio::io_context io;
        if (argc < 3 || argc > 4)
            throw std::runtime_error("Использование: client port ca.pem|- [hostname]");
        ssl::context tls(ssl::context::tls_client);
        if (!SSL_CTX_set_min_proto_version(tls.native_handle(), TLS1_2_VERSION))
            throw std::runtime_error("Не удалось ограничить версию TLS");
        if (std::string(argv[2]) == "-") tls.set_default_verify_paths();
        else tls.load_verify_file(argv[2]);
        bool failed = false;
        std::make_shared<WebSocketClient>(io, tls, failed)->start(
            net::parsePort(argv[1]), argc == 4 ? argv[3] : "localhost");
        io.run();
        return failed ? 1 : 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

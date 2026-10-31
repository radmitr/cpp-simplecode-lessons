#include "../common/boost_net.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
using Tcp = asio::ip::tcp;
using Error = boost::system::error_code;

class WebSocketClient : public std::enable_shared_from_this<WebSocketClient>
{
public:
    WebSocketClient(asio::io_context& io, bool& failed) : stream_(io), timer_(io), failed_(failed) {}
    void start(std::uint16_t port)
    {
        stream_.read_message_max(4096);
        stream_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));
        timer_.expires_after(std::chrono::seconds(5));
        timer_.async_wait([self = shared_from_this()](Error error) {
            if (!error) self->finish(asio::error::timed_out);
        });
        stream_.next_layer().async_connect({asio::ip::address_v4::loopback(), port},
            [self = shared_from_this(), port](Error error) {
                if (error) return self->finish(error);
                self->stream_.async_handshake("127.0.0.1:" + std::to_string(port), "/events",
                    [self](Error handshakeError) {
                        if (handshakeError) return self->finish(handshakeError);
                        self->readEvent();
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
                        self->finish(closeError == websocket::error::closed
                            ? Error{} : closeError ? closeError : Error(asio::error::fault));
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
        stream_.next_layer().close(ignored);
        if (error)
        {
            failed_ = true;
            std::cerr << "WebSocket client: " << error.message() << '\n';
        }
        else std::cout << "WebSocket complete: " << received_ << " events\n";
    }
    websocket::stream<Tcp::socket> stream_;
    asio::steady_timer timer_;
    beast::flat_buffer input_;
    const std::string ack_ = "ACK 3";
    int received_ = 0;
    bool& failed_;
    bool finished_ = false;
};

int main(int argc, char* argv[])
{
    try
    {
        asio::io_context io;
        bool failed = false;
        std::make_shared<WebSocketClient>(io, failed)->start(net::portArgument(argc, argv, 42019));
        io.run();
        return failed ? 1 : 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

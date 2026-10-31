#ifndef NETWORKING_DEMO_NET_HPP
#define NETWORKING_DEMO_NET_HPP

// Небольшой учебный слой над WinSock/POSIX. IPv4 используется по умолчанию.
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include <algorithm>
#include <cerrno>
#include <charconv>
#include <chrono>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

namespace net
{
#ifdef _WIN32
using Handle = SOCKET;
using AddressLength = int;
inline constexpr Handle invalid = INVALID_SOCKET;
inline int lastError() { return WSAGetLastError(); }
inline bool interrupted(int error) { return error == WSAEINTR; }
inline bool wouldBlock(int error) { return error == WSAEWOULDBLOCK; }
inline bool connecting(int error) { return wouldBlock(error) || error == WSAEINPROGRESS; }
#else
using Handle = int;
using AddressLength = socklen_t;
inline constexpr Handle invalid = -1;
inline int lastError() { return errno; }
inline bool interrupted(int error) { return error == EINTR; }
inline bool wouldBlock(int error) { return error == EAGAIN || error == EWOULDBLOCK; }
inline bool connecting(int error) { return error == EINPROGRESS || interrupted(error); }
#endif

[[noreturn]] inline void fail(const char* operation, int error = lastError())
{
#ifdef _WIN32
    throw std::runtime_error(std::string(operation) + ": WinSock error " + std::to_string(error));
#else
    throw std::runtime_error(std::string(operation) + ": "
                             + std::error_code(error, std::generic_category()).message());
#endif
}

class Runtime
{
public:
    Runtime()
    {
#ifdef _WIN32
        WSADATA data{};
        const int error = WSAStartup(MAKEWORD(2, 2), &data);
        if (error != 0) fail("WSAStartup", error);
#endif
    }
    ~Runtime()
    {
#ifdef _WIN32
        WSACleanup();
#endif
    }
    Runtime(const Runtime&) = delete;
    Runtime& operator=(const Runtime&) = delete;
};

class Socket
{
public:
    Socket() = default;
    explicit Socket(Handle handle) : handle_(handle) {}
    ~Socket() { close(); }
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&& other) noexcept : handle_(std::exchange(other.handle_, invalid)) {}
    Socket& operator=(Socket&& other) noexcept
    {
        if (this != &other)
        {
            close();
            handle_ = std::exchange(other.handle_, invalid);
        }
        return *this;
    }
    Handle get() const { return handle_; }

private:
    void close() noexcept
    {
        if (handle_ == invalid) return;
#ifdef _WIN32
        closesocket(handle_);
#else
        ::close(handle_);
#endif
        handle_ = invalid;
    }
    Handle handle_ = invalid;
};

inline void nonblocking(const Socket& socket)
{
#ifdef _WIN32
    u_long enabled = 1;
    if (ioctlsocket(socket.get(), FIONBIO, &enabled) != 0) fail("ioctlsocket");
#else
    const int flags = fcntl(socket.get(), F_GETFL, 0);
    if (flags < 0 || fcntl(socket.get(), F_SETFL, flags | O_NONBLOCK) < 0) fail("fcntl");
#endif
}

inline Socket makeSocket(int type, int family = AF_INET)
{
    Socket result(::socket(family, type, 0));
    if (result.get() == invalid) fail("socket");
    nonblocking(result);
    return result;
}

using Clock = std::chrono::steady_clock;
using Deadline = Clock::time_point;
inline Deadline after(std::chrono::milliseconds duration) { return Clock::now() + duration; }

class Timeout : public std::runtime_error
{
public:
    Timeout() : std::runtime_error("socket deadline expired") {}
};

class PeerClosed : public std::runtime_error
{
public:
    PeerClosed() : std::runtime_error("peer closed the connection") {}
};

inline void waitReady(const Socket& socket, bool writing, Deadline deadline)
{
    for (;;)
    {
        const auto remaining = std::chrono::duration_cast<std::chrono::microseconds>(
            deadline - Clock::now());
        if (remaining.count() <= 0) throw Timeout();
        timeval timeout{};
        timeout.tv_sec = static_cast<long>(remaining.count() / 1000000);
        timeout.tv_usec = static_cast<long>(remaining.count() % 1000000);
        fd_set ready;
        fd_set errors;
        FD_ZERO(&ready);
        FD_ZERO(&errors);
#ifndef _WIN32
        // FD_SET для дескриптора вне диапазона привёл бы к UB.
        if (socket.get() < 0 || socket.get() >= FD_SETSIZE)
            throw std::runtime_error("socket is outside the select() descriptor range");
#endif
        FD_SET(socket.get(), &ready);
        FD_SET(socket.get(), &errors);
#ifdef _WIN32
        const int count = select(0, writing ? nullptr : &ready,
                                 writing ? &ready : nullptr, &errors, &timeout);
#else
        const int count = select(socket.get() + 1, writing ? nullptr : &ready,
                                 writing ? &ready : nullptr, &errors, &timeout);
#endif
        if (count > 0) return; // Следующая операция проверит её реальный результат.
        if (count == 0) throw Timeout();
        const int error = lastError();
        if (!interrupted(error)) fail("select", error);
    }
}

inline sockaddr_in loopback(std::uint16_t port)
{
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(port); // Порядок байтов сети.
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1.
    return address;
}

inline void bindLoopback(const Socket& socket, std::uint16_t port)
{
    const auto address = loopback(port);
    if (::bind(socket.get(), reinterpret_cast<const sockaddr*>(&address), sizeof(address)) != 0)
        fail("bind");
}

inline std::uint16_t localPort(const Socket& socket)
{
    sockaddr_storage address{};
    AddressLength length = sizeof(address);
    if (getsockname(socket.get(), reinterpret_cast<sockaddr*>(&address), &length) != 0)
        fail("getsockname");
    if (address.ss_family == AF_INET)
        return ntohs(reinterpret_cast<const sockaddr_in*>(&address)->sin_port);
    if (address.ss_family == AF_INET6)
        return ntohs(reinterpret_cast<const sockaddr_in6*>(&address)->sin6_port);
    throw std::runtime_error("unsupported socket address family");
}

inline std::uint16_t parsePort(std::string_view text, bool allowZero = false)
{
    unsigned int value = 0;
    const auto parsed = std::from_chars(text.data(), text.data() + text.size(), value);
    if (parsed.ec != std::errc{} || parsed.ptr != text.data() + text.size()
        || value > 65535 || (!allowZero && value == 0))
        throw std::runtime_error("Invalid port (expected 1..65535; server also accepts 0)");
    return static_cast<std::uint16_t>(value);
}

inline std::uint16_t portArgument(int argc, char* argv[], std::uint16_t fallback,
                                  bool allowZero = false)
{
    if (argc > 2) throw std::runtime_error("Usage: program [port]");
    return argc == 1 ? fallback : parsePort(argv[1], allowZero);
}

inline Socket listenTcp(std::uint16_t port)
{
    auto socket = makeSocket(SOCK_STREAM);
    bindLoopback(socket, port);
    if (::listen(socket.get(), 8) != 0) fail("listen");
    return socket;
}

inline Socket accept(const Socket& listener, Deadline deadline)
{
    for (;;)
    {
        waitReady(listener, false, deadline);
        Socket client(::accept(listener.get(), nullptr, nullptr));
        if (client.get() != invalid)
        {
            nonblocking(client);
            return client;
        }
        const int error = lastError();
        if (!wouldBlock(error) && !interrupted(error)) fail("accept", error);
    }
}

inline Socket connectAddress(const sockaddr* address, AddressLength length, Deadline deadline)
{
    auto socket = makeSocket(SOCK_STREAM, address->sa_family);
    if (::connect(socket.get(), address, length) == 0)
        return socket;
    const int error = lastError();
    if (!connecting(error)) fail("connect", error);
    waitReady(socket, true, deadline);
    int result = 0;
    AddressLength resultLength = sizeof(result);
    if (getsockopt(socket.get(), SOL_SOCKET, SO_ERROR,
                   reinterpret_cast<char*>(&result), &resultLength) != 0)
        fail("getsockopt");
    if (result != 0) fail("connect", result);
    return socket;
}

inline Socket connectLoopback(std::uint16_t port, Deadline deadline)
{
    const auto address = loopback(port);
    return connectAddress(reinterpret_cast<const sockaddr*>(&address), sizeof(address), deadline);
}

inline void sendAll(const Socket& socket, std::string_view message, Deadline deadline,
                    std::size_t maxChunk = INT_MAX)
{
    if (maxChunk == 0) throw std::runtime_error("maxChunk must be positive");
    std::size_t sent = 0;
    while (sent < message.size())
    {
        waitReady(socket, true, deadline);
        const int size = static_cast<int>(std::min(
            {message.size() - sent, maxChunk, static_cast<std::size_t>(INT_MAX)}));
#ifdef MSG_NOSIGNAL
        constexpr int flags = MSG_NOSIGNAL;
#else
        constexpr int flags = 0;
#endif
        const auto count = ::send(socket.get(), message.data() + sent, size, flags);
        if (count > 0) sent += static_cast<std::size_t>(count);
        else if (count == 0) throw PeerClosed();
        else
        {
            const int error = lastError();
            if (!wouldBlock(error) && !interrupted(error)) fail("send", error);
        }
    }
}

inline std::size_t receiveSome(const Socket& socket, char* buffer, std::size_t capacity,
                               Deadline deadline)
{
    for (;;)
    {
        waitReady(socket, false, deadline);
        const int size = static_cast<int>(std::min(capacity, static_cast<std::size_t>(INT_MAX)));
        const auto count = ::recv(socket.get(), buffer, size, 0);
        if (count >= 0) return static_cast<std::size_t>(count); // 0 означает конец потока.
        const int error = lastError();
        if (!wouldBlock(error) && !interrupted(error)) fail("recv", error);
    }
}

inline std::string receiveExact(const Socket& socket, std::size_t size, Deadline deadline)
{
    std::string result(size, '\0');
    std::size_t received = 0;
    while (received < size)
    {
        const auto count = receiveSome(socket, result.data() + received, size - received, deadline);
        if (count == 0) throw PeerClosed();
        received += count;
    }
    return result;
}

inline std::string receiveLine(const Socket& socket, Deadline deadline,
                               std::size_t limit = 4096)
{
    std::string result;
    // По одному байту для наглядности. В рабочей библиотеке используют буфер.
    for (;;)
    {
        char ch = '\0';
        if (receiveSome(socket, &ch, 1, deadline) == 0) throw PeerClosed();
        if (ch == '\n') return result;
        if (result.size() == limit) throw std::runtime_error("line is too large");
        result += ch;
    }
}

inline void sendFrame(const Socket& socket, std::string_view body, Deadline deadline)
{
    if (body.size() > 65536) throw std::runtime_error("frame is too large");
    const std::uint32_t size = htonl(static_cast<std::uint32_t>(body.size()));
    std::string frame(reinterpret_cast<const char*>(&size), sizeof(size));
    frame.append(body);
    sendAll(socket, frame, deadline, 3); // Намеренно отправляем небольшими кусками.
}

inline std::string receiveFrame(const Socket& socket, Deadline deadline)
{
    const std::string header = receiveExact(socket, sizeof(std::uint32_t), deadline);
    std::uint32_t size = 0;
    // memcpy не требует выравнивания строки под uint32_t.
    std::memcpy(&size, header.data(), sizeof(size));
    size = ntohl(size);
    if (size > 65536) throw std::runtime_error("frame is too large");
    return receiveExact(socket, size, deadline);
}
} // namespace net
#endif

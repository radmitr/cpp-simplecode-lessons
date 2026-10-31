#ifndef NETWORKING_BOOST_NET_HPP
#define NETWORKING_BOOST_NET_HPP

// Задаём поддерживаемую версию Windows до подключения заголовков WinSock/Asio.
#if defined(_WIN32) && !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0601
#endif
#include "net.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <memory>

namespace async_net
{
namespace asio = boost::asio;
using Tcp = asio::ip::tcp;
using Error = boost::system::error_code;
} // namespace async_net
#endif

// C++11 — псевдонимы using; сетевые операции предоставляет Boost.Asio.
#ifndef NETWORKING_BOOST_NET_HPP
#define NETWORKING_BOOST_NET_HPP

// Задаём поддерживаемую версию Windows до подключения заголовков WinSock/Asio.
#if defined(_WIN32) && !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0601
#endif
// Платформенный пролог: настройки Windows/WinSock до Boost и console.hpp.
#include "net.hpp"

#include <iostream>
#include <memory>

#include <boost/asio.hpp>

namespace async_net
{
namespace asio = boost::asio;
using Tcp = asio::ip::tcp;
using Error = boost::system::error_code;
} // namespace async_net
#endif

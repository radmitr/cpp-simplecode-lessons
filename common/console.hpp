// C++98 — пространство имён и inline-функция; Windows API относится к платформе.
#ifndef CPP_LESSONS_CONSOLE_HPP
#define CPP_LESSONS_CONSOLE_HPP

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace console
{
inline void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}
} // namespace console

#endif

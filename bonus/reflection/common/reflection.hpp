#pragma once
#if !defined(__cpp_impl_reflection) || __cpp_impl_reflection < 202506L
#error "Use GCC 16+ with -std=c++26 -freflection for this lesson"
#endif
#include <meta>
#include <string>
#include <string_view>
#include <type_traits>
#include <optional>
#include <utility>
#include "check.hpp"

namespace reflection_demo
{
template<class T, class F>
void for_each_field(T&& object, F&& visitor)
{
    using U = std::remove_cvref_t<T>;
    template for (constexpr auto member : std::define_static_array(
        std::meta::nonstatic_data_members_of(^^U, std::meta::access_context::unprivileged())))
    {
        // Метаданные известны при компиляции, значения полей читаются при запуске.
        visitor(std::meta::identifier_of(member), object.[:member:]);
    }
}

template<class E>
constexpr std::string_view enum_name(E value)
{
    static_assert(std::is_enum_v<E>);
    template for (constexpr auto item : std::define_static_array(std::meta::enumerators_of(^^E)))
        if (value == [:item:]) return std::meta::identifier_of(item);
    return {};
}

template<class E>
constexpr std::optional<E> enum_value(std::string_view name)
{
    template for (constexpr auto item : std::define_static_array(std::meta::enumerators_of(^^E)))
        if (name == std::meta::identifier_of(item)) return [:item:];
    return std::nullopt;
}
}

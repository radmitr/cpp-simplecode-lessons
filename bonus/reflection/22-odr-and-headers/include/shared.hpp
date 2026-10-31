#pragma once
#include "../../common/reflection.hpp"
struct Shared { int id; int age; };
template<class T> consteval std::size_t public_field_count()
{
    return std::meta::nonstatic_data_members_of(^^T,
        std::meta::access_context::unprivileged()).size();
}


int count_from_other_translation_unit();

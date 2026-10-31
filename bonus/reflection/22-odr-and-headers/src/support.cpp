#include "shared.hpp"
int count_from_other_translation_unit() { return static_cast<int>(public_field_count<Shared>()); }

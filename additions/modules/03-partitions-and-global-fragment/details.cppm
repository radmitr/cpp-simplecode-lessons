// C++20 — global module fragment и раздел реализации.
module;
// Заголовок подключается до объявления именованного модуля.
#include <algorithm>

module geometry:details;
int positive(int value) { return std::max(value, 0); }

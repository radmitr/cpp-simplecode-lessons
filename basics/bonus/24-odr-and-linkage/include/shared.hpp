// C++98 — inline-функции и несколько единиц трансляции.
#pragma once
#include "../../common/check.hpp"
inline int shared_answer() { return 42; }
int answer_from_other_file();

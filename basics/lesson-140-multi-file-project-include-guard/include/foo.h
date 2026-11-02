// C++98 — защита заголовков от повторного включения.
#pragma once

#ifndef _FOO_H_
#define _FOO_H_

#include <iostream>
#include "bar.h"

void foo();
void foo2();

#endif // !_FOO_H_

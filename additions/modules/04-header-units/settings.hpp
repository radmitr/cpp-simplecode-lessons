// C++20 — заголовок для header unit; C++98 — inline-функция и макрос.
#ifndef MODULE_DEMO_SETTINGS_HPP
#define MODULE_DEMO_SETTINGS_HPP
#define DEMO_FACTOR 3
inline int scaled(int value) { return value * DEMO_FACTOR; }
#endif

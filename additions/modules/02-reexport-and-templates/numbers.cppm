// C++20 — экспортируемый шаблон в интерфейсе модуля.
export module numbers;
export template<class T> constexpr T square(T value) { return value * value; }

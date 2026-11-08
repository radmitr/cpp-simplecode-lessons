// C++20 — интерфейс именованного модуля и export.
export module arithmetic;

export int add(int left, int right);
export struct Pair { int first; int second; };
export int total(Pair value);

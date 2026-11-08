// C++20 — единица реализации именованного модуля.
module arithmetic;

int checked_demo_sum(int left, int right) { return left + right; }
int add(int left, int right) { return checked_demo_sum(left, right); }
int total(Pair value) { return add(value.first, value.second); }

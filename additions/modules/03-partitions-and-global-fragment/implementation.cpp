// C++20 — единица реализации и импорт внутреннего раздела.
module geometry;
import :details;

int area(Rectangle r) { return positive(r.width) * positive(r.height); }
int border(Rectangle r) { return 2 * (positive(r.width) + positive(r.height)); }

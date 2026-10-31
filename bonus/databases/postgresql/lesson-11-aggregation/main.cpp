#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE sales(category text, amount integer);
            INSERT INTO sales VALUES ('books', 100), ('books', 200),
                                     ('games', 50), ('games', 70)
        )");
        // WHERE фильтрует исходные строки, HAVING — уже сгруппированные результаты.
        auto result = db::exec(conn.get(), R"(
            SELECT category, count(*) AS items, sum(amount) AS total
            FROM sales
            WHERE amount > 0
            GROUP BY category
            HAVING sum(amount) >= 150
            ORDER BY total DESC, category
        )");
        db::print(result);
        db::require(PQntuples(result.get()) == 1 && db::value(result, 0, 2) == "300",
                    "Expected books total 300");
    });
}

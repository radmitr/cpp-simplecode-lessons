#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE products(id integer PRIMARY KEY, name text, price integer);
            INSERT INTO products VALUES (1, 'Pen', 20), (2, 'Book', 70), (3, 'Bag', 90)
        )");
        // WHERE отбирает строки; ORDER BY задаёт порядок; LIMIT ограничивает результат.
        auto result = db::exec(conn.get(), R"(
            SELECT name, price FROM products
            WHERE price >= 50
            ORDER BY price DESC, id
            LIMIT 2
        )");
        db::print(result);
        db::require(db::value(result) == "Bag", "Expected descending price order");
    });
}

#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        // TEMP-таблица принадлежит соединению и удалится при его закрытии.
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE products (
                id bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
                name text NOT NULL,
                price numeric(10, 2) NOT NULL,
                active boolean NOT NULL DEFAULT true,
                created_at timestamptz NOT NULL DEFAULT now()
            );
            INSERT INTO products(name, price) VALUES ('Notebook', 12.50)
        )");
        auto result = db::exec(conn.get(),
            "SELECT id, name, price, active FROM products");
        db::print(result);
        db::require(db::value(result, 0, 2) == "12.50", "numeric must preserve decimals");
    });
}

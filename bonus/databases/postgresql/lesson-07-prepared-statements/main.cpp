#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE products(id integer PRIMARY KEY, name text);
            INSERT INTO products VALUES (1, 'Pen'), (2, 'Book')
        )");
        // Именованный запрос существует в рамках этого соединения.
        db::checked(conn.get(), PQprepare(conn.get(), "find_product",
            "SELECT name FROM products WHERE id = $1::int", 1, nullptr));
        for (const char* id : {"1", "2"}) {
            const char* values[] = {id};
            auto result = db::checked(conn.get(),
                PQexecPrepared(conn.get(), "find_product", 1, values, nullptr, nullptr, 0));
            std::cout << id << ": " << db::value(result) << '\n';
        }
        db::exec(conn.get(), "DEALLOCATE find_product");
    });
}

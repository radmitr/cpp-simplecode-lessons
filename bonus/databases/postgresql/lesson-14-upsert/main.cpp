#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), "CREATE TEMP TABLE inventory(sku text PRIMARY KEY, quantity integer)");
        const auto add = [&](const char* sku, const char* quantity) {
            auto result = db::params(conn.get(), R"(
                INSERT INTO inventory(sku, quantity) VALUES ($1::text, $2::int)
                ON CONFLICT (sku) DO UPDATE
                SET quantity = inventory.quantity + EXCLUDED.quantity
                RETURNING sku, quantity
            )", {sku, quantity});
            db::print(result);
        };
        add("book", "2");
        add("book", "3"); // Та же строка: 2 + 3, а не ошибка UNIQUE.
        auto ignored = db::exec(conn.get(),
            "INSERT INTO inventory VALUES ('book', 999) ON CONFLICT DO NOTHING");
        std::cout << "DO NOTHING affected: " << PQcmdTuples(ignored.get()) << '\n';
        db::require(std::string(PQcmdTuples(ignored.get())) == "0", "Expected a skipped row");
    });
}

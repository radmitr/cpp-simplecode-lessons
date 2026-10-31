#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE customers(id integer PRIMARY KEY, name text NOT NULL);
            CREATE TEMP TABLE orders(
                id integer PRIMARY KEY,
                customer_id integer NOT NULL REFERENCES customers(id),
                total integer NOT NULL
            );
            INSERT INTO customers VALUES (1, 'Alice'), (2, 'Bob');
            INSERT INTO orders VALUES (10, 1, 100), (11, 1, 200)
        )");
        std::cout << "INNER JOIN:\n";
        db::print(db::exec(conn.get(), R"(
            SELECT c.name, o.id, o.total FROM customers c
            INNER JOIN orders o ON o.customer_id = c.id ORDER BY o.id
        )"));
        std::cout << "LEFT JOIN:\n";
        db::print(db::exec(conn.get(), R"(
            SELECT c.name, o.id FROM customers c
            LEFT JOIN orders o ON o.customer_id = c.id ORDER BY c.id, o.id
        )"));
        try {
            db::exec(conn.get(), "INSERT INTO orders VALUES (12, 999, 50)");
            throw std::runtime_error("Expected foreign key violation");
        } catch (const db::Error& error) {
            db::require(error.state == "23503", "Unexpected SQLSTATE");
            std::cout << "Foreign key rejected: " << error.state << '\n';
        }
    });
}

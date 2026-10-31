#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE users(
                id integer PRIMARY KEY,
                email text NOT NULL UNIQUE,
                age integer NOT NULL CHECK (age >= 0)
            );
            INSERT INTO users VALUES (1, 'alice@example.test', 20)
        )");
        const auto rejected = [&](const char* sql, const char* expected) {
            try {
                db::exec(conn.get(), sql);
            } catch (const db::Error& error) {
                db::require(error.state == expected, "Unexpected SQLSTATE");
                std::cout << "Rejected: " << error.state << '\n';
                return;
            }
            throw std::runtime_error("Constraint did not reject invalid data");
        };
        rejected("INSERT INTO users VALUES (2, 'alice@example.test', 30)", "23505");
        rejected("INSERT INTO users VALUES (3, 'bob@example.test', -1)", "23514");
        rejected("INSERT INTO users VALUES (4, NULL, 10)", "23502");
        // Здесь autocommit: ошибка одного INSERT не отменяет предыдущую строку.
        auto result = db::exec(conn.get(), "SELECT count(*) FROM users");
        std::cout << "Valid rows: " << db::value(result) << '\n';
    });
}

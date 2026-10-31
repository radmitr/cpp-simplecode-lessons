#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE accounts(id integer PRIMARY KEY, balance integer CHECK(balance >= 0));
            INSERT INTO accounts VALUES (1, 100), (2, 100)
        )");
        {
            db::Transaction transaction(conn.get()); // BEGIN
            db::exec(conn.get(), "UPDATE accounts SET balance = balance - 30 WHERE id = 1");
            db::exec(conn.get(), "UPDATE accounts SET balance = balance + 30 WHERE id = 2");
            transaction.commit(); // COMMIT: обе записи сохраняются вместе.
        }
        try {
            db::Transaction transaction(conn.get());
            db::exec(conn.get(), "UPDATE accounts SET balance = balance - 20 WHERE id = 1");
            throw std::runtime_error("Simulated application failure");
            // При выходе из области видимости деструктор выполняет ROLLBACK.
        } catch (const std::runtime_error& error) {
            db::require(std::string(error.what()) == "Simulated application failure",
                        error.what());
            std::cout << "Second transfer rolled back\n";
        }
        auto result = db::exec(conn.get(), "SELECT id, balance FROM accounts ORDER BY id");
        db::print(result);
        db::require(db::value(result, 0, 1) == "70" && db::value(result, 1, 1) == "130",
                    "Transfer was not atomic");
    });
}

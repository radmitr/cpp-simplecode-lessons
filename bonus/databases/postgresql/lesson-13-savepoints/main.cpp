#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), "CREATE TEMP TABLE items(id integer PRIMARY KEY)");
        db::Transaction transaction(conn.get());
        db::exec(conn.get(), "INSERT INTO items VALUES (1)");
        db::exec(conn.get(), "SAVEPOINT optional_step");
        try {
            db::exec(conn.get(), "INSERT INTO items VALUES (1)");
            throw std::runtime_error("Expected a duplicate key");
        } catch (const db::Error& error) {
            db::require(error.state == "23505", "Unexpected SQLSTATE");
            // После SQL-ошибки транзакция не принимает обычные команды до отката.
            db::exec(conn.get(), "ROLLBACK TO SAVEPOINT optional_step");
        }
        db::exec(conn.get(), "RELEASE SAVEPOINT optional_step");
        db::exec(conn.get(), "INSERT INTO items VALUES (2)");
        transaction.commit();
        std::cout << "Committed ids:\n";
        db::print(db::exec(conn.get(), "SELECT id FROM items ORDER BY id"));
    });
}

#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto admin = db::connect();
        db::SharedSchema schema(admin.get());
        const std::string table = schema.table();
        db::exec(admin.get(), ("CREATE TABLE " + table + "(id integer PRIMARY KEY, n integer); INSERT INTO " + table + " VALUES (1, 10)").c_str());
        auto owner = db::connect();
        auto contender = db::connect();
        db::Transaction owner_transaction(owner.get());
        db::exec(owner.get(), ("SELECT n FROM " + table + " WHERE id = 1 FOR UPDATE").c_str());
        // Обычный SELECT не ждёт блокировку строки и читает видимую зафиксированную версию.
        std::cout << "Plain SELECT: "
                  << db::value(db::exec(contender.get(), ("SELECT n FROM " + table).c_str())) << '\n';
        try {
            db::Transaction contender_transaction(contender.get());
            db::exec(contender.get(), "SET LOCAL lock_timeout = '200ms'");
            db::exec(contender.get(), ("UPDATE " + table + " SET n = n + 1 WHERE id = 1").c_str());
            throw std::runtime_error("Expected lock timeout");
        } catch (const db::Error& error) {
            db::require(error.state == "55P03", "Expected lock_not_available");
            std::cout << "Contender timed out: " << error.state << '\n';
        }
        owner_transaction.commit(); // Освобождает блокировку строки.
        auto changed = db::exec(contender.get(),
            ("UPDATE " + table + " SET n = n + 1 WHERE id = 1 RETURNING n").c_str());
        std::cout << "Retry after COMMIT: " << db::value(changed) << '\n';
        db::require(db::value(changed) == "11", "Retry must update exactly once");
    });
}

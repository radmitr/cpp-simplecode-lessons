#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        std::cout << "Connected: " << PQdb(conn.get()) << '\n';
        std::cout << "Server version: " << PQserverVersion(conn.get()) << '\n';
        // SELECT возвращает PGRES_TUPLES_OK; результат живёт до вызова PQclear.
        auto result = db::exec(conn.get(), "SELECT 2 + 3 AS answer");
        db::require(PQntuples(result.get()) == 1, "Expected one row");
        std::cout << "Answer: " << db::value(result) << '\n';
    });
}

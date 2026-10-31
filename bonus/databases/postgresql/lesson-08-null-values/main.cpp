#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), "CREATE TEMP TABLE contacts(id integer, nickname text)");
        db::params(conn.get(), "INSERT INTO contacts VALUES ($1::int, $2::text)", {"1", nullptr});
        db::params(conn.get(), "INSERT INTO contacts VALUES ($1::int, $2::text)", {"2", ""});
        auto result = db::exec(conn.get(), "SELECT id, nickname FROM contacts ORDER BY id");
        for (int row = 0; row < PQntuples(result.get()); ++row) {
            const bool missing = PQgetisnull(result.get(), row, 1) != 0;
            std::cout << db::value(result, row, 0) << ": "
                      << (missing ? "<NULL>" : "<empty string>") << '\n';
        }
        auto count = db::exec(conn.get(),
            "SELECT count(*) FROM contacts WHERE nickname IS NULL");
        std::cout << "NULL count: " << db::value(count) << '\n';
        db::require(db::value(count) == "1", "NULL differs from an empty string");
    });
}

#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), "CREATE TEMP TABLE devices(id integer PRIMARY KEY, settings jsonb NOT NULL)");
        db::params(conn.get(), "INSERT INTO devices VALUES ($1::int, $2::jsonb)",
                   {"1", R"({"name":"sensor","enabled":true,"threshold":25})"});
        // -> возвращает JSON; ->> извлекает текст.
        auto result = db::params(conn.get(), R"(
            SELECT settings->>'name', settings->>'threshold'
            FROM devices WHERE settings @> $1::jsonb
        )", {R"({"enabled":true})"});
        db::print(result);
        db::exec(conn.get(), R"(
            UPDATE devices SET settings = jsonb_set(settings, '{threshold}', '30'::jsonb)
            WHERE id = 1
        )");
        auto changed = db::exec(conn.get(),
            "SELECT settings->>'threshold' FROM devices WHERE id = 1");
        std::cout << "Threshold: " << db::value(changed) << '\n';
        db::require(db::value(changed) == "30", "Expected changed JSON field");
    });
}

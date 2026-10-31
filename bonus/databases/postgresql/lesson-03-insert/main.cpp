#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE notes (
                id integer GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
                title text NOT NULL
            )
        )");
        // RETURNING получает id в том же запросе, без SELECT max(id).
        auto first = db::exec(conn.get(),
            "INSERT INTO notes(title) VALUES ('Learn SQL') RETURNING id, title");
        db::print(first);
        auto more = db::exec(conn.get(), R"(
            INSERT INTO notes(title) VALUES ('Learn C++'), ('Practice')
            RETURNING id, title
        )");
        db::print(more);
        db::require(PQntuples(more.get()) == 2, "Expected two inserted rows");
    });
}

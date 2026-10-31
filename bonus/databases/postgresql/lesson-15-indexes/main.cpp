#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE events AS
                SELECT i AS id, 'payload-' || i AS payload FROM generate_series(1, 30000) AS i;
            ANALYZE events
        )");
        std::cout << "Before index:\n";
        db::print(db::exec(conn.get(),
            "EXPLAIN (ANALYZE, BUFFERS, COSTS OFF, TIMING OFF) SELECT * FROM events WHERE id = 23456"));
        db::exec(conn.get(), "CREATE INDEX events_id_idx ON events(id)");
        db::exec(conn.get(), "ANALYZE events");
        std::cout << "After index:\n";
        db::print(db::exec(conn.get(),
            "EXPLAIN (ANALYZE, BUFFERS, COSTS OFF, TIMING OFF) SELECT * FROM events WHERE id = 23456"));
        auto result = db::exec(conn.get(), "SELECT payload FROM events WHERE id = 23456");
        db::require(db::value(result) == "payload-23456", "Index must not change query results");
    });
}

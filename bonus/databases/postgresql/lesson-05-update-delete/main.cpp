#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), R"(
            CREATE TEMP TABLE tasks(id integer PRIMARY KEY, title text, done boolean);
            INSERT INTO tasks VALUES (1, 'Read', false), (2, 'Practice', false)
        )");
        // WHERE обязателен по смыслу задачи: без него изменятся все строки.
        auto updated = db::exec(conn.get(),
            "UPDATE tasks SET done = true WHERE id = 1 RETURNING id, done");
        db::print(updated);
        auto deleted = db::exec(conn.get(),
            "DELETE FROM tasks WHERE done = true RETURNING title");
        std::cout << "Deleted: " << PQcmdTuples(deleted.get()) << '\n';
        auto missing = db::exec(conn.get(), "DELETE FROM tasks WHERE id = 999");
        std::cout << "Missing id affected: " << PQcmdTuples(missing.get()) << '\n';
        db::require(std::string(PQcmdTuples(missing.get())) == "0", "Expected no affected rows");
    });
}

#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), "CREATE SCHEMA IF NOT EXISTS backup_demo");
        db::exec(conn.get(), R"(
            CREATE TABLE IF NOT EXISTS backup_demo.notes(id integer PRIMARY KEY, title text NOT NULL)
        )");
        db::exec(conn.get(), R"(
            INSERT INTO backup_demo.notes VALUES (1, 'Learn PostgreSQL'), (2, 'Verify restore')
            ON CONFLICT (id) DO UPDATE SET title = EXCLUDED.title
        )");
        std::cout << "Backup source:\n";
        db::print(db::exec(conn.get(), "SELECT id, title FROM backup_demo.notes ORDER BY id"));
        std::cout << "Run scripts/backup-restore.sh to dump and verify a separate restored database.\n";
    });
}

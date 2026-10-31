#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), "CREATE TEMP TABLE notes(id integer, title text)");
        const std::string title = "O'Reilly; DROP TABLE notes; --";
        // Значения передаются отдельно: кавычка и точка с запятой остаются текстом.
        db::params(conn.get(), "INSERT INTO notes VALUES ($1::int, $2::text)",
                   {"1", title.c_str()});
        auto result = db::params(conn.get(),
            "SELECT title FROM notes WHERE id = $1::int", {"1"});
        std::cout << "Stored literally: " << db::value(result) << '\n';
        db::require(db::value(result) == title, "Parameter changed");
        // Параметром нельзя подставить имя таблицы или направление ORDER BY.
        // Для таких элементов выбирают заранее разрешённый вариант SQL.
    });
}

#include "../common/db.hpp"
#include <cstddef>

int main() {
    return db::run([] {
        auto conn = db::connect();
        db::exec(conn.get(), "CREATE TEMP TABLE readings(id integer, value integer)");
        // COPY FROM STDIN принимает поток через соединение, а не файл на сервере.
        db::Result begin(PQexec(conn.get(), "COPY readings FROM STDIN WITH (FORMAT csv)"), &PQclear);
        db::require(begin && PQresultStatus(begin.get()) == PGRES_COPY_IN, PQerrorMessage(conn.get()));
        const std::string csv = "1,10\n2,20\n3,30\n";
        db::require(PQputCopyData(conn.get(), csv.data(), static_cast<int>(csv.size())) == 1,
                    PQerrorMessage(conn.get()));
        db::require(PQputCopyEnd(conn.get(), nullptr) == 1, PQerrorMessage(conn.get()));
        // Завершение передачи ещё не означает успешного выполнения COPY.
        while (PGresult* raw = PQgetResult(conn.get())) {
            db::checked(conn.get(), raw);
        }
        std::cout << "Imported rows: "
                  << db::value(db::exec(conn.get(), "SELECT count(*) FROM readings")) << '\n';

        db::Result output(PQexec(conn.get(),
            "COPY (SELECT * FROM readings ORDER BY id) TO STDOUT WITH (FORMAT csv)"), &PQclear);
        db::require(output && PQresultStatus(output.get()) == PGRES_COPY_OUT, PQerrorMessage(conn.get()));
        std::string exported;
        char* buffer = nullptr;
        int length = 0;
        while ((length = PQgetCopyData(conn.get(), &buffer, 0)) > 0) {
            std::unique_ptr<char, decltype(&PQfreemem)> owned(buffer, &PQfreemem);
            exported.append(owned.get(), static_cast<std::size_t>(length));
        }
        db::require(length == -1, PQerrorMessage(conn.get()));
        while (PGresult* raw = PQgetResult(conn.get())) {
            db::checked(conn.get(), raw);
        }
        std::cout << "Exported CSV:\n" << exported;
        db::require(exported == csv, "COPY round trip changed the data");
    });
}

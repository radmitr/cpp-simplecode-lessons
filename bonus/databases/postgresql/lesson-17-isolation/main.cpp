#include "../common/db.hpp"

int main() {
    return db::run([] {
        auto admin = db::connect();
        db::SharedSchema schema(admin.get());
        const std::string table = schema.table();
        db::exec(admin.get(), ("CREATE TABLE " + table + "(n integer); INSERT INTO " + table + " VALUES (10)").c_str());
        auto reader = db::connect();
        auto writer = db::connect();
        const auto demonstrate = [&](bool repeatable) {
            db::exec(writer.get(), ("UPDATE " + table + " SET n = 10").c_str());
            db::Transaction transaction(reader.get());
            db::exec(reader.get(), repeatable ? "SET TRANSACTION ISOLATION LEVEL REPEATABLE READ"
                                             : "SET TRANSACTION ISOLATION LEVEL READ COMMITTED");
            const auto before = db::exec(reader.get(), ("SELECT n FROM " + table).c_str());
            // Другое соединение фиксирует UPDATE между двумя SELECT читателя.
            db::exec(writer.get(), ("UPDATE " + table + " SET n = 20").c_str());
            const auto after = db::exec(reader.get(), ("SELECT n FROM " + table).c_str());
            std::cout << (repeatable ? "REPEATABLE READ: " : "READ COMMITTED: ")
                      << db::value(before) << " -> " << db::value(after) << '\n';
            db::require(db::value(after) == (repeatable ? "10" : "20"), "Unexpected snapshot");
            transaction.commit();
        };
        demonstrate(false);
        demonstrate(true);
    });
}

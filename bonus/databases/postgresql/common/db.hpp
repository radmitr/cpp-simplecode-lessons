#pragma once

// Debian/Ubuntu размещают заголовки libpq в подкаталоге postgresql.
#if __has_include(<libpq-fe.h>)
#include <libpq-fe.h>
#elif __has_include(<postgresql/libpq-fe.h>)
#include <postgresql/libpq-fe.h>
#else
#error "Install the PostgreSQL development package (libpq headers)."
#endif

#include <cstdlib>
#include <filesystem>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace db {

using Connection = std::unique_ptr<PGconn, decltype(&PQfinish)>;
using Result = std::unique_ptr<PGresult, decltype(&PQclear)>;

class Error : public std::runtime_error {
public:
    std::string state;
    Error(std::string message, std::string sqlstate)
        : std::runtime_error(std::move(message)), state(std::move(sqlstate)) {}
};

inline void require(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

inline std::filesystem::path lab_home() {
    if (const char* value = std::getenv("PGLESSONS_HOME")) return value;
    auto root = std::filesystem::path(__FILE__).parent_path();
    for (int i = 0; i < 4; ++i) root = root.parent_path();
    return (root / ".local/postgresql").lexically_normal();
}

inline Connection connect(const char* database = "cpp_lessons") {
    // Пароль читает libpq из файла, он не попадает в исходник или командную строку.
    const auto passfile = (lab_home() / "pgpass.conf").u8string();
    const char* port = std::getenv("PGLESSONS_PORT");
    const char* keys[] = {"host", "port", "dbname", "user", "passfile",
                          "connect_timeout", "client_encoding", "application_name", nullptr};
    const char* values[] = {"127.0.0.1", port ? port : "55432", database,
                            "cpp_student", passfile.c_str(), "3", "UTF8",
                            "cpp_simplecode_lessons", nullptr};
    Connection conn(PQconnectdbParams(keys, values, 0), &PQfinish);
    require(static_cast<bool>(conn), "PQconnectdbParams: out of memory");
    require(PQstatus(conn.get()) == CONNECTION_OK, PQerrorMessage(conn.get()));
    // Ограничиваем зависшие запросы; lesson-18 дополнительно задаёт lock_timeout.
    Result settings(PQexec(conn.get(), "SET statement_timeout = '5s'"), &PQclear);
    require(settings && PQresultStatus(settings.get()) == PGRES_COMMAND_OK,
            PQerrorMessage(conn.get()));
    return conn;
}

inline Result checked(PGconn* conn, PGresult* raw) {
    Result result(raw, &PQclear);
    require(static_cast<bool>(result), PQerrorMessage(conn));
    const auto status = PQresultStatus(result.get());
    if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK) {
        const char* state = PQresultErrorField(result.get(), PG_DIAG_SQLSTATE);
        throw Error(PQresultErrorMessage(result.get()), state ? state : "");
    }
    return result;
}

inline Result exec(PGconn* conn, const char* sql) {
    return checked(conn, PQexec(conn, sql));
}

inline Result params(PGconn* conn, const char* sql,
                     std::initializer_list<const char*> values) {
    // $1, $2... передаются отдельно от SQL. nullptr обозначает SQL NULL.
    return checked(conn, PQexecParams(conn, sql, static_cast<int>(values.size()),
                                     nullptr, values.begin(), nullptr, nullptr, 0));
}

inline std::string value(const Result& result, int row = 0, int column = 0) {
    require(row >= 0 && row < PQntuples(result.get()) && column >= 0 &&
            column < PQnfields(result.get()), "Result cell is out of range");
    require(!PQgetisnull(result.get(), row, column), "Use PQgetisnull before reading NULL");
    return PQgetvalue(result.get(), row, column);
}

inline void print(const Result& result) {
    for (int row = 0; row < PQntuples(result.get()); ++row) {
        for (int column = 0; column < PQnfields(result.get()); ++column) {
            if (column) std::cout << " | ";
            std::cout << (PQgetisnull(result.get(), row, column)
                          ? "NULL" : PQgetvalue(result.get(), row, column));
        }
        std::cout << '\n';
    }
}

class Transaction {
    PGconn* conn_;
    bool active_ = true;
public:
    explicit Transaction(PGconn* conn) : conn_(conn) { exec(conn_, "BEGIN"); }
    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;
    ~Transaction() {
        if (active_) {
            // Деструктор не бросает исключение, даже при потере соединения.
            Result ignored(PQexec(conn_, "ROLLBACK"), &PQclear);
        }
    }
    void commit() {
        require(PQtransactionStatus(conn_) == PQTRANS_INTRANS,
                "Cannot commit an inactive or failed transaction");
        exec(conn_, "COMMIT");
        active_ = false;
    }
};

// Только для двух уроков с несколькими соединениями: отдельная схема на запуск.
class SharedSchema {
    PGconn* conn_;
    std::string name_;
public:
    explicit SharedSchema(PGconn* conn) : conn_(conn) {
        const auto pid = exec(conn_, "SELECT pg_backend_pid()");
        name_ = "cpp_lab_" + value(pid);
        exec(conn_, ("CREATE SCHEMA " + name_).c_str());
    }
    SharedSchema(const SharedSchema&) = delete;
    SharedSchema& operator=(const SharedSchema&) = delete;
    ~SharedSchema() {
        Result ignored(PQexec(conn_, ("DROP SCHEMA " + name_ + " CASCADE").c_str()), &PQclear);
    }
    std::string table() const { return name_ + ".counter"; }
};

template<class Function>
int run(Function function) {
    try {
        function();
        return 0;
    } catch (const Error& error) {
        std::cerr << "SQLSTATE " << error.state << ": " << error.what() << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
    }
    return 1;
}

} // namespace db

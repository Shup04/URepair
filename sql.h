#ifndef SQL_H
#define SQL_H

#include <sqlite3.h>
#include <iostream>
#include <string>

void setupDatabase() {
    sqlite3* db;
    char* errMsg = nullptr;

    // Open database
    if (sqlite3_open("urepair.db", &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // SQL query for creating the table
    const char* sql =
        "CREATE TABLE IF NOT EXISTS Contractors ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT,"
        "skillset TEXT,"
        "minPrice REAL,"
        "maxPrice REAL"
        ");";

    // Execute SQL
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully." << std::endl;
    }

    // Close database
    sqlite3_close(db);
}
#endif // SQL_H
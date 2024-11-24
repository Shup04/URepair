#ifndef SQL_H
#define SQL_H

#include <sqlite3.h>
#include <iostream>
#include <string>

void setupDatabase() {
    sqlite3* db;
    int rc = sqlite3_open("urepair.db", &db);

    if (rc) {
        std::cerr << "Error: Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Create tables if they don't exist
    const char* contractorTable = R"(
        CREATE TABLE IF NOT EXISTS Contractors (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            skillset TEXT NOT NULL,
            rate INTEGER NOT NULL
        );
    )";

    const char* jobTable = R"(
        CREATE TABLE IF NOT EXISTS Jobs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            description TEXT NOT NULL,
            requiredSkill TEXT NOT NULL,
            price REAL NOT NULL,
            urgency INTEGER NOT NULL
        );
    )";

    // Execute SQL commands
    char* errMsg = nullptr;
    sqlite3_exec(db, contractorTable, nullptr, nullptr, &errMsg);
    if (errMsg) {
        std::cerr << "Error creating Contractors table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_exec(db, jobTable, nullptr, nullptr, &errMsg);
    if (errMsg) {
        std::cerr << "Error creating Jobs table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    std::cout << "Database initialized successfully!\n";

    // Close database connection
    sqlite3_close(db);
}
#endif // SQL_H
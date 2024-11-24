#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <fstream>

#include "structs.h"
#include <sqlite3.h>

// Implementations for readability
void addContractor(sqlite3* db, const std::string& name, const int& rate,  const std::string& skillset);
void listContractors(sqlite3* db);
void deleteContractor(sqlite3* db, const int& id);
void updateContractor(sqlite3* db, const int& id, const std::string& name, const int& rate,  const std::string& skillset);

void addContractor(sqlite3* db, const std::string& name, const int& rate,  const std::string& skillset) {
    const char* sql = "INSERT INTO contractors (name, rate, skillset) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Bind the variables to the prepared statement
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC); 
    sqlite3_bind_int(stmt, 2, rate);                            
    sqlite3_bind_text(stmt, 3, skillset.c_str(), -1, SQLITE_STATIC); 


    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    } else {
        std::cout << "Inserted successfully!\n";
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
}

void listContractors(sqlite3* db) {
    const char* sql = "SELECT * FROM contractors;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "Contractors:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        const unsigned char* skillset = sqlite3_column_text(stmt, 2);
        int rate = sqlite3_column_double(stmt, 3);

        std::cout << "ID: " << id
                  << ", Name: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
                  << ", Skillset: " << (skillset ? reinterpret_cast<const char*>(skillset) : "NULL")
                  << ", Hourly Rate: " << rate << std::endl;
    }

    sqlite3_finalize(stmt);
}

void deleteContractor(sqlite3* db, const int& id) {
    const char* sql = "DELETE FROM contractors WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Bind the variables to the prepared statement
    sqlite3_bind_int(stmt, 1, id);                            

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    } else {
        std::cout << "Deleted successfully!\n";
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
}

void updateContractor(sqlite3* db, const int& id, const std::string& name, const int& rate,  const std::string& skillset) {
    const char* sql = "UPDATE contractors SET name = ?, rate = ?, skillset = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Bind the variables to the prepared statement
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC); 
    sqlite3_bind_int(stmt, 2, rate);                            
    sqlite3_bind_text(stmt, 3, skillset.c_str(), -1, SQLITE_STATIC); 
    sqlite3_bind_int(stmt, 4, id);                            

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    } else {
        std::cout << "Updated successfully!\n";
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
}

std::vector<Contractor> searchContractors(sqlite3* db, const int& rate, const std::string& skillset) {
    //Contractor c; // Declare contractor object
    const char* sql = "SELECT * FROM contractors WHERE rate <= ? AND skillset = ?;";
    sqlite3_stmt* stmt = nullptr;
    std::vector<Contractor> matches;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return matches; // Return default contractor
    }

    // Bind the variables to the prepared statement
    if (sqlite3_bind_int(stmt, 1, rate) != SQLITE_OK) {
        std::cerr << "Failed to bind rate: " << sqlite3_errmsg(db) << "\n";
        sqlite3_finalize(stmt);
        return matches; // Return default contractor
    }

    if (sqlite3_bind_text(stmt, 2, skillset.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind skillset: " << sqlite3_errmsg(db) << "\n";
        sqlite3_finalize(stmt);
        return matches; // Return default contractor
    }

    // Execute the statement and fetch results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Contractor c;
        c.id = sqlite3_column_int(stmt, 0);
        c.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        c.skillset = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        c.rate = sqlite3_column_int(stmt, 3);
        matches.push_back(c);
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    return matches;
}



#endif //FUNCTIONS_H
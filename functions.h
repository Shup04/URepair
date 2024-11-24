#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <fstream>

#include "structs.h"
#include <sqlite3.h>

void addUser(const std::string& name, const std::string& email);
void listUsers();
void registerContractor(std::string name, std::vector<std::string> skillset, float minPrice, float maxPrice);
void addJob(std::string description, std::string requiredSkill, float price, int urgency);

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


/*
std::vector<Contractor> contractors;

void registerContractor(std::string name, std::vector<std::string> skillset, float minPrice, float maxPrice) {
    Contractor c = {name, skillset, minPrice, maxPrice};
    contractors.push_back(c);
    std::cout << "SUCCESS: Contractor registered!\n";
}
*/

std::priority_queue<Job, std::vector<Job>, JobComparator> jobs;

void addJob(std::string description, std::string requiredSkill, float price, int urgency) {
    Job j = {description, requiredSkill, price, urgency};
    jobs.push(j);
    std::cout << "SUCCESS: Job added!\n";
}

#endif //FUNCTIONS_H
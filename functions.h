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

void addUser(const std::string& name, const std::string& email) {
    sqlite3* db;
    int rc = sqlite3_open("urepair.db", &db);
    
}

std::vector<Contractor> getContractors(sqlite3* db) {
    sqlite3_stmt* stmt;
    std::vector<Contractor> contractors;
    const char* listQuery = "SELECT id, name, skillset FROM Contractors;";

    if (sqlite3_prepare_v2(db, listQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return contractors;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Contractor c;
        c.id = sqlite3_column_int(stmt, 0); // Column 0: id
        c.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); // Column 1: name
        c.skillset = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // Column 2: skillset

        contractors.push_back(c);
    }

    sqlite3_finalize(stmt); // Clean up the prepared statement
    return contractors;
}

void listContractors(sqlite3* db) {
    std::vector<Contractor> contractors = getContractors(db);
    for (const auto& c : contractors) {
        std::cout << "ID: " << c.id << ", Name: " << c.name << ", Skillset: " << c.skillset << "\n";
    }
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
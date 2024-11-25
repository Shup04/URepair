#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <fstream>

#include "structs.h"
#include <sqlite3.h>

// Contractor Helper Functions
void addContractor(sqlite3* db, const std::string& name, const int& rate,  const std::string& skillset);
std::vector<Contractor> listContractors(sqlite3* db);
void deleteContractor(sqlite3* db, const int& id);
void updateContractor(sqlite3* db, const int& id, const std::string& name, const int& rate,  const std::string& skillset);
std::vector<Contractor> searchContractors(sqlite3* db, const int& rate, const std::string& skillset);
Contractor getContractor(sqlite3* db, const int& id);

// Job Helper Functions
void addJob(sqlite3* db, const std::string& description, const std::string& requiredSkill, float price, int urgency);
std::vector<Job> listJobs(sqlite3* db);
void deleteJob(sqlite3* db, int jobId);
void updateJob(sqlite3* db, int jobId, const std::string& field, const std::string& newValue);
std::vector<Job> matchJobsToContractor(sqlite3* db, int contractorId);


// Contractor Fucntions
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

std::vector<Contractor> listContractors(sqlite3* db) {
    const char* sql = "SELECT * FROM contractors;";
    sqlite3_stmt* stmt;
    std::vector <Contractor> contractors; 
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return contractors;
    }

    std::cout << "Contractors:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        const unsigned char* skillset = sqlite3_column_text(stmt, 2);
        int rate = sqlite3_column_double(stmt, 3);

        Contractor c;
        c.id = sqlite3_column_int(stmt, 0);
        c.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        c.skillset = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        c.rate = sqlite3_column_int(stmt, 3);
        contractors.push_back(c);

        std::cout << "ID: " << id
                  << ", Name: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
                  << ", Skillset: " << (skillset ? reinterpret_cast<const char*>(skillset) : "NULL")
                  << ", Hourly Rate: " << rate << std::endl;
    }

    sqlite3_finalize(stmt);
    return contractors;
}

Contractor getContractor(sqlite3* db, const int& id) {
    const char* sql = "SELECT * FROM contractors WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    Contractor c;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return c; // Return default contractor
    }

    // Bind the id to the prepared statement
    if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
        std::cerr << "Failed to bind id: " << sqlite3_errmsg(db) << "\n";
        sqlite3_finalize(stmt);
        return c; // Return default contractor
    }

    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        c.id = sqlite3_column_int(stmt, 0);
        c.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        c.skillset = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        c.rate = sqlite3_column_int(stmt, 3);
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    return c;
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


// Job Functions
void addJob(sqlite3* db, const std::string& description, const std::string& requiredSkill, float price, int urgency) {
    const char* sql = "INSERT INTO jobs (description, requiredSkill, price, urgency) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Bind the variables to the prepared statement
    sqlite3_bind_text(stmt, 1, description.c_str(), -1, SQLITE_STATIC); 
    sqlite3_bind_text(stmt, 2, requiredSkill.c_str(), -1, SQLITE_STATIC); 
    sqlite3_bind_double(stmt, 3, price);                            
    sqlite3_bind_int(stmt, 4, urgency);                            

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    } else {
        std::cout << "Job added successfully!\n";
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
}

std::vector<Job> listJobs(sqlite3* db) {
    const char* sql = "SELECT * FROM jobs;";
    sqlite3_stmt* stmt = nullptr;
    std::vector<Job> jobs;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return jobs;
    }

    std::cout << "Jobs:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* description = sqlite3_column_text(stmt, 1);
        const unsigned char* requiredSkill = sqlite3_column_text(stmt, 2);
        float price = static_cast<float>(sqlite3_column_double(stmt, 3));
        int urgency = sqlite3_column_int(stmt, 4);

        Job j;

        j.id = sqlite3_column_int(stmt, 0);
        j.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        j.requiredSkill = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        j.price = sqlite3_column_int(stmt, 3);
        j.urgency = sqlite3_column_int(stmt, 4);
        jobs.push_back(j);

        std::cout << "ID: " << id
                  << ", Description: " << (description ? reinterpret_cast<const char*>(description) : "NULL")
                  << ", Required Skill: " << (requiredSkill ? reinterpret_cast<const char*>(requiredSkill) : "NULL")
                  << ", Price: " << price
                  << ", Urgency: " << urgency << std::endl;
    }

    sqlite3_finalize(stmt);
    return jobs;
}

void deleteJob(sqlite3* db, int jobId) {
    const char* sql = "DELETE FROM jobs WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Bind the jobId to the prepared statement
    sqlite3_bind_int(stmt, 1, jobId);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    } else {
        std::cout << "Job deleted successfully!\n";
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
}

void updateJob(sqlite3* db, int jobId, const std::string& field, const std::string& newValue) {
    std::string sql = "UPDATE jobs SET " + field + " = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Bind the new value and jobId to the prepared statement
    sqlite3_bind_text(stmt, 1, newValue.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, jobId);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    } else {
        std::cout << "Job updated successfully!\n";
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
}

std::vector<Job> matchJobsToContractor(sqlite3* db, int contractorId) {
    vector<Job> allJobs = listJobs(db);
    Contractor c = getContractor(db, contractorId);
    vector<Job> matches;

    for (const auto& job : allJobs) {
        if ((job.requiredSkill == c.skillset) && (job.price <= c.rate)) {
           matches.push_back(job); 
        }
    }
    return matches
}

// Algorithm Functions
// Merge Sort Algorithm
std::vector<Contractor> sortContractorsByRate(std::vector<Contractor>& contractors) {
    auto merge = [](std::vector<Contractor>& contractors, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<Contractor> L(n1);
        std::vector<Contractor> R(n2);

        for (int i = 0; i < n1; ++i)
            L[i] = contractors[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = contractors[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i].rate <= R[j].rate) {
                contractors[k] = L[i];
                ++i;
            } else {
                contractors[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            contractors[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            contractors[k] = R[j];
            ++j;
            ++k;
        }
    };

    auto mergeSort = [&](std::vector<Contractor>& contractors, int left, int right, auto& mergeSortRef) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSortRef(contractors, left, mid, mergeSortRef);
            mergeSortRef(contractors, mid + 1, right, mergeSortRef);

            merge(contractors, left, mid, right);
        }
    };

    mergeSort(contractors, 0, contractors.size() - 1, mergeSort);
    return contractors;
}

std::vector<Job> sortJobsByPrice(std::vector<Job>& jobs) {
    auto merge = [](std::vector<Job>& jobs, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<Job> L(n1);
        std::vector<Job> R(n2);

        for (int i = 0; i < n1; ++i)
            L[i] = jobs[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = jobs[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i].price <= R[j].price) {
                jobs[k] = L[i];
                ++i;
            } else {
                jobs[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            jobs[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            jobs[k] = R[j];
            ++j;
            ++k;
        }
    };

    auto mergeSort = [&](std::vector<Job>& jobs, int left, int right, auto& mergeSortRef) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSortRef(jobs, left, mid, mergeSortRef);
            mergeSortRef(jobs, mid + 1, right, mergeSortRef);

            merge(jobs, left, mid, right);
        }
    };

    mergeSort(jobs, 0, jobs.size() - 1, mergeSort);
    return jobs;
}

// Priority Heap
std::priority_queue<Job, std::vector<Job>, JobComparator> prioritizeJobs(std::vector<Job>& jobs) {
    std::priority_queue<Job, std::vector<Job>, JobComparator> pq;
    for (const auto& job : jobs) {
        pq.push(job);
    }
    return pq;
}

Job getMostUrgentJob(std::priority_queue<Job>& jobQueue);




#endif //FUNCTIONS_H
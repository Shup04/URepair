#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
#include <queue>

// Define Contractor struct
struct Contractor {
    int id = 0;
    std::string name = "";
    int rate = 0;
    std::string skillset = "";
};

// Define Job struct
struct Job {
    int id = 0;
    std::string description = "";
    std::string requiredSkill = "";
    float price = 0.0;
    int urgency = 0; // Lower value = higher urgency
};

// Define a comparator for Job priority
struct JobComparator {
    bool operator()(const Job& a, const Job& b) {
        if (a.urgency == b.urgency) {
            return a.price < b.price; // Lower price comes last if urgency is equal
        }
        return a.urgency > b.urgency; // Higher urgency comes first
    }
};

#endif // STRUCTS_H

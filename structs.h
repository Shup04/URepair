#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
#include <queue>

// Define Contractor struct
struct Contractor {
    int id;
    std::string name;
    std::vector<std::string> skillset;
    float minPrice;
    float maxPrice;
};

// Define Job struct
struct Job {
    std::string description;
    std::string requiredSkill;
    float price;
    int urgency; // Lower value = higher urgency
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

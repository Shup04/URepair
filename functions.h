#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <fstream>

#include "structs.h"

void addUser(const std::string& name, const std::string& email);
void listUsers();
void registerContractor(std::string name, std::vector<std::string> skillset, float minPrice, float maxPrice);
void addJob(std::string description, std::string requiredSkill, float price, int urgency);

void addUser(const std::string& name, const std::string& email) {
    std::ofstream file("users.txt", std::ios::app); // Append to the file
    file << name << "," << email << "\n";
    file.close();
    std::cout << "SUCCESS: User added!" << std::endl;
}

void listUsers() {
    std::ifstream file("users.txt");
    std::string line;

    std::cout << "USER LIST:" << std::endl;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

std::vector<Contractor> contractors;

void registerContractor(std::string name, std::vector<std::string> skillset, float minPrice, float maxPrice) {
    Contractor c = {name, skillset, minPrice, maxPrice};
    contractors.push_back(c);
    std::cout << "SUCCESS: Contractor registered!\n";
}

std::priority_queue<Job, std::vector<Job>, JobComparator> jobs;

void addJob(std::string description, std::string requiredSkill, float price, int urgency) {
    Job j = {description, requiredSkill, price, urgency};
    jobs.push(j);
    std::cout << "SUCCESS: Job added!\n";
}

#endif //FUNCTIONS_H
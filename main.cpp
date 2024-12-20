#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <functional>


#include "functions.h"
#include "structs.h"
#include "sql.h"

int main(int argc, char* argv[]) {
    sqlite3* db;
    int rc = sqlite3_open("urepair.db", &db);

    std::cout << "Welcome to URepair!" << std::endl;
        std::cout << "Setting up the database..." << std::endl;
        setupDatabase();
        std::cout << "Database setup complete!" << std::endl;
        
        // Frontent doesnt specify function to call
        if (argc < 2) {
            std::cerr << "ERROR: No operation specified!" << std::endl;
            return 1;
        }

        std::string operation = argv[1];

        // Add User
        if (operation == "addUser" && argc == 5) {
            std::cout << argv[2] << " " << argv[3] << " " << argv[4] << std::endl;
            addContractor(db, argv[2], std::stoi(argv[3]), argv[4]); // Pass name, rate, and skillsets
        }

        // List/Get all Contractors
        else if (operation == "listContractors")
        {
            listContractors(db);
        }

        // Delete Contractor
        else if (operation == "deleteContractor" && argc == 3)
        {
            deleteContractor(db, std::stoi(argv[2]));
        }

        // Update Contractor
        else if (operation == "updateContractor" && argc == 6)
        {
            updateContractor(db, std::stoi(argv[2]), argv[3], std::stoi(argv[4]), argv[5]);
        }

        // Search Contractors, returns a vector of suitable contractors unordered.
        else if (operation == "searchContractors" && argc == 4)
        {
            std::vector<Contractor> matches = searchContractors(db, std::stoi(argv[2]), argv[3]);

            for (auto &Contractor : matches)
            {
                std::cout << Contractor.name << std::endl;
            }
        }

        // Add Job
        else if (operation == "addJob" && argc == 6)
        {
            addJob(db, argv[2], argv[3], std::stof(argv[4]), std::stoi(argv[5]));
        }

        // List/Get all Jobs
        else if (operation == "listJobs")
        {
            listJobs(db);
        }

        // Delete Job
        else if (operation == "deleteJob" && argc == 3)
        {
            deleteJob(db, std::stoi(argv[2]));
        }

        // Update Job
        else if (operation == "updateJob" && argc == 5)
        {
            updateJob(db, std::stoi(argv[2]), argv[3], argv[4]);
        }

        // Sort by contractor rating
        else if (operation == "sortContractorsByRate")
        {
            std::vector<Contractor> contractors = listContractors(db);
            std::vector<Contractor> sortedContractors = sortContractorsByRate(contractors);
            for (auto &Contractor : sortedContractors)
            {
                std::cout << Contractor.name << std::endl;
            }
        }

        // Sort jobs by price
        else if (operation == "sortJobsByPrice")
        {
            std::vector<Job> jobs = listJobs(db);
            std::vector<Job> sortedJobs = sortJobsByPrice(jobs);
            for (auto &Job : sortedJobs)
            {
                std::cout << Job.description << std::endl;
            }
        }

        // prioritize Jobs
        else if (operation == "prioritizeJobs")
        {
            std::vector<Job> jobs = listJobs(db);
            std::priority_queue<Job, std::vector<Job>, JobComparator> pq = prioritizeJobs(jobs);
            while (!pq.empty())
            {
                std::cout << pq.top().description << std::endl;
                pq.pop();
            }
        }

        // get most urgent job
        else if (operation == "getMostUrgentJob")
        {
            std::vector<Job> jobs = listJobs(db);
            std::priority_queue<Job, std::vector<Job>, JobComparator> priorityJobs = prioritizeJobs(jobs);
            Job mostUrgentJob = getMostUrgentJob(priorityJobs);
            std::cout << mostUrgentJob.description << std::endl;
        }

        else if (operation == "searchContractorInBST" && argc == 4)
        {
            int rate = std::stoi(argv[2]);
            std::string skillset = argv[3];
            try
            {
                Contractor contractor = searchContractorInBST(db, rate, skillset);
                std::cout << "Contractor Found: " << contractor.name << ", Rate: " << contractor.rate
                          << ", Skills: " << contractor.skillset << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        else if (operation == "searchContractorsByRateRange" && argc == 4)
        {
            int minRate = std::stoi(argv[2]);
            int maxRate = std::stoi(argv[3]);

            BST<Contractor, ContractorComparator> contractorTree = generateContractorBST(db);
            std::vector<Contractor> contractors = searchContractorsByRateRange(contractorTree, minRate, maxRate);

            for (const auto &contractor : contractors)
            {
                std::cout << contractor.name << ", Rate: " << contractor.rate
                          << ", Skills: " << contractor.skillset << std::endl;
            }
        }

        else if (operation == "getLowestRateContractor")
        {
            BST<Contractor, ContractorComparator> contractorTree = generateContractorBST(db);
            try
            {
                Contractor contractor = getLowestRateContractor(contractorTree);
                std::cout << "Lowest Rate Contractor: " << contractor.name << ", Rate: " << contractor.rate
                          << ", Skills: " << contractor.skillset << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        else if (operation == "getHighestRateContractor")
        {
            BST<Contractor, ContractorComparator> contractorTree = generateContractorBST(db);
            try
            {
                Contractor contractor = getHighestRateContractor(contractorTree);
                std::cout << "Highest Rate Contractor: " << contractor.name << ", Rate: " << contractor.rate
                          << ", Skills: " << contractor.skillset << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        else if (operation == "matchContractorsToSkill" && argc == 3)
        {
            std::string skillset = argv[2];
            BST<Contractor, ContractorComparator> contractorTree = generateContractorBST(db);
            std::vector<Contractor> contractors = matchContractorsToSkill(contractorTree, skillset);

            for (const auto &contractor : contractors)
            {
                std::cout << contractor.name << ", Rate: " << contractor.rate
                          << ", Skills: " << contractor.skillset << std::endl;
            }
        }

        else if (operation == "searchJobsByPriceRange" && argc == 4) {
            float minPrice = std::stof(argv[2]);
            float maxPrice = std::stof(argv[3]);

            BST<Job, JobPriceComparator> jobTree = generateJobBST<JobPriceComparator>(db); // Use price comparator
            std::vector<Job> jobs = searchJobsByPriceRange(jobTree, minPrice, maxPrice);

            for (const auto& job : jobs) {
                std::cout << "Job: " << job.description << ", Price: " << job.price
                        << ", Urgency: " << job.urgency << std::endl;
            }
        }

        else if (operation == "matchJobsToContractorRate" && argc == 3) {
            int contractorRate = std::stoi(argv[2]);
            BST<Job, JobPriceComparator> jobTree = generateJobBST<JobPriceComparator>(db); // Use price comparator
            std::vector<Job> jobs = matchJobsToContractorRate(jobTree, contractorRate);

            for (const auto& job : jobs) {
                std::cout << "Job: " << job.description << ", Price: " << job.price
                        << ", Urgency: " << job.urgency << std::endl;
            }
        }


        // deletes the database
        else if (operation == "deleteDB") {
            std::filesystem::remove("urepair.db");
            std::cout << "Database deleted successfully!" << std::endl;
        } 
        
        else {
            std::cerr << "ERROR: Invalid operation or arguments!" << std::endl;
            return 1;
        }

    return 0;
}

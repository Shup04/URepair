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
        if (operation == "addUser" && argc == 5) {
            std::cout << argv[2] << " " << argv[3] << " " << argv[4] << std::endl;
            addContractor(db, argv[2], std::stoi(argv[3]), argv[4]); // Pass name, rate, and skillsets
        }
        
        else if (operation == "listContractors") {
            listContractors(db);
        } 

        else if (operation == "deleteContractor" && argc == 3) {
            deleteContractor(db, std::stoi(argv[2]));
        }

        else if (operation == "updateContractor" && argc == 6) {
            updateContractor(db, std::stoi(argv[2]), argv[3], std::stoi(argv[4]), argv[5]);
        }
        
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

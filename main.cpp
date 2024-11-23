#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: No operation specified!" << std::endl;
        return 1;
    }

    std::string operation = argv[1];
    if (operation == "addUser" && argc == 4) {
        addUser(argv[2], argv[3]); // Pass name and email
    } else if (operation == "listUsers") {
        listUsers();
    } else {
        std::cerr << "ERROR: Invalid operation or arguments!" << std::endl;
        return 1;
    }

    return 0;
}

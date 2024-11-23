#include <iostream>
#include <string>
#include <fstream>

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
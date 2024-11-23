#include <iostream>
#include <string>
#include <fstream>

void createUser(const std::string& name, const std::string& email) {
    std::ofstream file("users.txt", std::ios::app); // Append to the file
    file << name << "," << email << "\n";
    file.close();
    std::cout << "SUCCESS: User added!" << std::endl;
}
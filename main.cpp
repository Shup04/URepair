#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <functions.cpp>


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

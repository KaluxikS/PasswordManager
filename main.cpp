#include "PasswordManager.h"
#include <iostream>

int main() {
    std::string masterPassword, filename;
    std::cout << "Enter password: ";
    std::cin >> masterPassword;
    std::cout << "Enter file to open: ";
    std::cin >> filename;

    PasswordManager passwordManager(masterPassword, filename);
    passwordManager.run();


}
#include "PasswordManager.h"
#include <iostream>

int main() {
    std::string masterPassword;
    std::cout << "Enter password: ";
    std::cin >> masterPassword;

    PasswordManager passwordManager(masterPassword);
    passwordManager.run();


}
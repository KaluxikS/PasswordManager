#include "PasswordManager.h"
#include <iostream>

int main() {
    std::string masterPassword;
    std::cout << "Enter password: "; //test commit
    std::cin >> masterPassword;

    PasswordManager passwordManager(masterPassword);
    passwordManager.run();


}
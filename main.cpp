#include "PasswordManager.h"
#include <iostream>

int main() {
    std::string masterPassword;
    std::cout << "Podaj haslo: ";
    std::cin >> masterPassword;

    PasswordManager passwordManager(masterPassword);
    passwordManager.run();


}
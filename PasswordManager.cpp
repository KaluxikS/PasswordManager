//
// Created by Piotr on 28.05.2023.
//

#include "PasswordManager.h"
#include <iostream>
#include <fstream>
#include <ctime>

PasswordManager::PasswordManager(const std::string& masterPassword)
        : filename("passwords.txt"), masterPassword(masterPassword) {
}

void PasswordManager::run() {
//    if(masterPassword != "d"){
//        std::cout << "Podano zle haslo!";
//        exit(0);
//    }
    loadDataFromFile();
    std::string choice = " ";

    while (choice != "7") {
        displayMenu();
        std::cout << "Choose option: ";
        std::cin >> choice;
        processOption(choice);
    }

}

void PasswordManager::loadDataFromFile() {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Password password = decryptPassword(line);
            passwords.push_back(password);
        }
        file.close();
    }
}

void PasswordManager::saveDataToFile() {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Password& password : passwords) {
            std::string encryptedLine = encryptPassword(password);
            file << encryptedLine << std::endl;
        }
        file.close();
    }
}

std::string PasswordManager::encryptPassword(const Password& password) {
    std::string encryptedLine = encrypt(password.name) + ";" +
                                encrypt(password.password) + ";" +
                                encrypt(password.category) + ";" +
                                encrypt(password.website) + ";" +
                                encrypt(password.login) + ";";
    return encryptedLine;
}

Password PasswordManager::decryptPassword(const std::string& encryptedLine) {

    Password password;
    std::string encryptedData = encryptedLine;

    size_t pos = encryptedData.find(';');
    password.name = decrypt(encryptedData.substr(0, pos));
    encryptedData.erase(0, pos + 1);

    pos = encryptedData.find(';');
    password.password = decrypt(encryptedData.substr(0, pos));
    passwordsString.push_back(password.password);
    encryptedData.erase(0, pos + 1);

    pos = encryptedData.find(';');
    password.category = decrypt(encryptedData.substr(0, pos));
    encryptedData.erase(0, pos + 1);

    pos = encryptedData.find(';');
    password.website = decrypt(encryptedData.substr(0, pos));
    encryptedData.erase(0, pos + 1);

    pos = encryptedData.find(';');
    password.login = decrypt(encryptedData.substr(0, pos));

    return password;
}

std::string PasswordManager::encrypt(std::string data) {
    std::reverse(data.begin(), data.end());
    for (char & i : data) {
        i = i + 52;
    }

    return data;
}

std::string PasswordManager::decrypt(std::string encryptedData) {
    std::reverse(encryptedData.begin(), encryptedData.end());
    for (char & i : encryptedData) {
        i = i - 52;
    }

    return encryptedData;
}

std::string PasswordManager::encryptTimestamp() {
    std::time_t timestamp = std::time(nullptr);
    std::string timestampStr = std::to_string(timestamp);
    return encrypt(timestampStr);
}

void PasswordManager::displayMenu() {
    std::cout << "----- MENU -----" << std::endl;
    std::cout << "1. Search password" << std::endl;
    std::cout << "2. Sort passwords" << std::endl;
    std::cout << "3. Add passwords" << std::endl;
    std::cout << "4. Edit password" << std::endl;
    std::cout << "5. Delete password" << std::endl;
    std::cout << "6. Add / delete category" << std::endl;
    std::cout << "7. End program" << std::endl;
}

void PasswordManager::processOption(const std::string& choice) {
    if (choice == "1") {
        searchPasswords();
    } else if (choice == "2") {
        sortPasswords();
    } else if (choice == "3") {
        addPassword();
    } else if (choice == "4") {
        editPassword();
    } else if (choice == "5") {
        deletePassword();
    } else if (choice == "6") {
        manageCategories();
    } else if (choice == "7") {
        saveDataToFile();
        std::cout << "Program will shut down." << std::endl;
    } else if (choice == "8") {
        displayAllPasswords();
    } else {
        std::cout << "Invalid option!" << std::endl;
    }
}

void PasswordManager::displayAllPasswords() {
    std::cout << "All passwords:" << std::endl;
    for (const Password& password : passwords) {
        std::cout << "Name: " << password.name << std::endl;
        std::cout << "Password: " << password.password << std::endl;
        std::cout << "Category: " << password.category << std::endl;
        std::cout << "Website: " << password.website << std::endl;
        std::cout << "Login: " << password.login << std::endl;
        std::cout << "--------------------------------------" << std::endl;
    }
}

bool PasswordManager::isAlreadyUsed(const std::vector<std::string> &vec, const std::string &str) {
    for (const auto& element : vec) {
        if (element == str) {
            return true;
        }
    }
    return false;
}

void PasswordManager::isPasswordStrong(const std::string &password) {
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasSpecialChar = false;
    bool hasNumber = false;

    for (char c : password) {
        if (isupper(c)) {
            hasUppercase = true;
        } else if (islower(c)) {
            hasLowercase = true;
        } else if (!isalnum(c)) {
            hasSpecialChar = true;
        } else if (isdigit(c)) {
            hasNumber = true;
        }
    }
    if(password.length() >= 8 && hasUppercase && hasLowercase && hasSpecialChar && hasNumber){
        std::cout << "Your password is safe!\n";
    }
    else {
        std::cout << "Your password is not safe, because it does not contain:" << std::endl;
        if (!hasUppercase) {
            std::cout << "- capital letter" << std::endl;
        }
        if (!hasLowercase) {
            std::cout << "- lower case letter" << std::endl;
        }
        if (!hasSpecialChar) {
            std::cout << "- special character" << std::endl;
        }
        if (!hasNumber) {
            std::cout << "- digits" << std::endl;
        }
        if (password.length() < 8) {
            std::cout << "- has less than 8 characters" << std::endl;
        }
    }
}

bool PasswordManager::comparePasswords(const Password &password1, const Password &password2,
                                       const std::string &sortBy) {
    if (sortBy == "name") {
        return password1.name < password2.name;
    } else if (sortBy == "category") {
        return password1.category < password2.category;
    } else if (sortBy == "website") {
        return password1.website < password2.website;
    } else if (sortBy == "login") {
        return password1.login < password2.login;
    } else {
        return password1.name < password2.name;
    }
}

std::string PasswordManager::generatePassword(int length, bool includeUppercase, bool includeLowercase, bool includeSpecialChars) {
    std::string password;

    std::string uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
    std::string specialChars = "!@#$%^&*()_+-={}[]|\\:;\"'<>,.?/";

    std::string charset = "";
    if (includeUppercase)
        charset += uppercaseChars;
    if (includeLowercase)
        charset += lowercaseChars;
    if (includeSpecialChars)
        charset += specialChars;

    if (charset.empty()) {
        std::cout << "You did not choose any options." << std::endl;
        return password;
    }

    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % charset.length();
        password += charset[randomIndex];
    }

    return password;
}

void PasswordManager::searchPasswords() {
    std::string searchParam;
    std::cout << "Enter a search parameter: ";
    std::cin >> searchParam;

    std::vector<Password> matchedPasswords;
    for (const Password& password : passwords) {
        if (password.name.find(searchParam) != std::string::npos ||
            password.category.find(searchParam) != std::string::npos ||
            password.website.find(searchParam) != std::string::npos ||
            password.login.find(searchParam) != std::string::npos)
        {
            matchedPasswords.push_back(password);
        }
    }

    if (matchedPasswords.empty()) {
        std::cout << "Did not find any password matching to the parameter." << std::endl;
    } else {
        std::cout << "Found passwords:" << std::endl;
        for (const Password& password : matchedPasswords) {
            std::cout << "Name: " << password.name << std::endl;
            std::cout << "Password: " << password.password << std::endl;
            std::cout << "Category: " << password.category << std::endl;
            std::cout << "Website: " << password.website << std::endl;
            std::cout << "Login: " << password.login << std::endl;
            std::cout << "--------------------------------------" << std::endl;
        }
    }
}

void PasswordManager::sortPasswords() {
    std::string sortBy;
    std::cout << "Choose sorting parameter (name, category, website, login): ";
    std::cin >> sortBy;

    if (sortBy != "name" && sortBy != "category" && sortBy != "website" && sortBy != "login") {
        std::cout << "Wrong sorting parameter!" << std::endl;
        return;
    }

    std::sort(passwords.begin(), passwords.end(), [sortBy, this](const Password& password1, const Password& password2) {
        return comparePasswords(password1, password2, sortBy);
    });

    std::cout << "Passwords sorted." << std::endl;
}

std::string PasswordManager::addSinglePasswordString() {
    std::string choice;
    std::string password;
    std::cout << "Would you like to generate your password automatically? (y/n): ";
    std::cin >> choice;

    if (choice == "y") {
        int length;
        bool includeUppercase;
        bool includeLowercase;
        bool includeSpecialChars;

        std::cout << "Enter password length: ";
        std::cin >> length;

        std::cout << "Should it contain capital letters? (y/n): ";
        std::cin >> choice;
        includeUppercase = (choice == "y");

        std::cout << "Should it contain small case letters? (y/n): ";
        std::cin >> choice;
        includeLowercase = (choice == "y");

        std::cout << "Should it contain special characters? (y/n): ";
        std::cin >> choice;
        includeSpecialChars = (choice == "y");

        password = generatePassword(length, includeUppercase, includeLowercase, includeSpecialChars);
        std::cout << "Generated password: " << password << std::endl;
    } else {
        std::cout << "Enter password: ";
        std::cin >> password;
        if (isAlreadyUsed(passwordsString, password)) {
            std::cout << "You have used this password. You can edit it later.\n";
        }
        isPasswordStrong(password);
        passwordsString.push_back(password);
    }
    return password;
}

void PasswordManager::addPassword() {
    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;

    std::cout << "Enter password name: ";
    std::cin >> name;

    password = addSinglePasswordString();

    std::cout << "Enter category: ";
    std::cin >> category;

    std::cout << "Enter website (optional): ";
    std::cin >> website;

    std::cout << "Enter login (optional): ";
    std::cin >> login;

    Password newPassword;
    newPassword.name = name;
    newPassword.password = password;
    newPassword.category = category;
    newPassword.website = website;
    newPassword.login = login;

    passwords.push_back(newPassword);

    std::cout << "Password added." << std::endl;
}

void PasswordManager::editPassword() {
    std::string name;
    std::cout << "Enter password name to edit: ";
    std::cin >> name;

    bool passwordExists = false;
    for (Password& password : passwords) {
        if (password.name == name) {
            passwordExists = true;

            std::cout << "Choose field to edit: " << std::endl;
            std::cout << "1. Name" << std::endl;
            std::cout << "2. Password" << std::endl;
            std::cout << "3. Category" << std::endl;
            std::cout << "4. Website" << std::endl;
            std::cout << "5. Login" << std::endl;
            std::cout << "Choose option: ";
            std::string option;
            std::cin >> option;

            if (option == "1") {
                std::cout << "Enter new name: ";
                std::cin >> password.name;
                std::cout << "Name changed." << std::endl;
            } else if (option == "2") {
                //std::string newPassword;
                password.password = addSinglePasswordString();
                std::cout << "Password changed." << std::endl;
            } else if (option == "3") {
                std::cout << "Enter new category: ";
                std::cin >> password.category;
                std::cout << "Category changed." << std::endl;
            } else if (option == "4") {
                std::cout << "Enter new website: ";
                std::cin >> password.website;
                std::cout << "Website changed." << std::endl;
            } else if (option == "5") {
                std::cout << "Enter new login: ";
                std::cin >> password.login;
                std::cout << "Login changed." << std::endl;
            } else {
                std::cout << "Wrong option!" << std::endl;
            }
            break;
        }
    }

    if (!passwordExists) {
        std::cout << "Could not find password with choosen name." << std::endl;
    }
}

void PasswordManager::deletePassword() {
    // Usuwanie wybranego hasła
}

void PasswordManager::manageCategories() {
    // Dodawanie i usuwanie kategorii
}

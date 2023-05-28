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
        std::cout << "Wybierz opcje: ";
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
    std::cout << "1. Wyszukaj hasla" << std::endl;
    std::cout << "2. Posortuj hasla" << std::endl;
    std::cout << "3. Dodaj haslo" << std::endl;
    std::cout << "4. Edytuj haslo" << std::endl;
    std::cout << "5. Usun haslo" << std::endl;
    std::cout << "6. Dodaj / usun kategorie" << std::endl;
    std::cout << "7. Zakoncz program" << std::endl;
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
        std::cout << "Program zostanie zakonczony." << std::endl;
    } else if (choice == "8") {
        displayAllPasswords();
    } else {
        std::cout << "Nieprawidlowa opcja!" << std::endl;
    }
}

void PasswordManager::displayAllPasswords() {
    std::cout << "Wszystkie hasla:" << std::endl;
    for (const Password& password : passwords) {
        std::cout << "Nazwa: " << password.name << std::endl;
        std::cout << "Haslo: " << password.password << std::endl;
        std::cout << "Kategoria: " << password.category << std::endl;
        std::cout << "Strona WWW: " << password.website << std::endl;
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
        std::cout << "Twoje haslo jest bezpieczne!\n";
    }
    else {
        std::cout << "Twoje haslo nie jest bezpieczne, bo nie zawiera:" << std::endl;
        if (!hasUppercase) {
            std::cout << "- wielkiej litery" << std::endl;
        }
        if (!hasLowercase) {
            std::cout << "- malej litery" << std::endl;
        }
        if (!hasSpecialChar) {
            std::cout << "- znaku specjalnego" << std::endl;
        }
        if (!hasNumber) {
            std::cout << "- cyfry" << std::endl;
        }
        if (password.length() < 8) {
            std::cout << "- ma mniej niz 8 znakow" << std::endl;
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
        // Domyślnie sortowanie po nazwie
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
        std::cout << "Nie wybrano żadnych opcji dla generowania hasła." << std::endl;
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
    std::cout << "Podaj parametr wyszukiwania: ";
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
        std::cout << "Nie znaleziono hasel pasujacych do podanego parametru." << std::endl;
    } else {
        std::cout << "Znalezione hasla:" << std::endl;
        for (const Password& password : matchedPasswords) {
            std::cout << "Nazwa: " << password.name << std::endl;
            std::cout << "Haslo: " << password.password << std::endl;
            std::cout << "Kategoria: " << password.category << std::endl;
            std::cout << "Strona WWW: " << password.website << std::endl;
            std::cout << "Login: " << password.login << std::endl;
            std::cout << "--------------------------------------" << std::endl;
        }
    }
}

void PasswordManager::sortPasswords() {
    std::string sortBy;
    std::cout << "Wybierz parametr sortowania (name, category, website, login): ";
    std::cin >> sortBy;

    // Sprawdzenie poprawności sortBy
    if (sortBy != "name" && sortBy != "category" && sortBy != "website" && sortBy != "login") {
        std::cout << "Nieprawidlowy parametr sortowania!" << std::endl;
        return;
    }

    // Sortowanie haseł
    std::sort(passwords.begin(), passwords.end(), [sortBy, this](const Password& password1, const Password& password2) {
        return comparePasswords(password1, password2, sortBy);
    });

    std::cout << "Hasla zostaly posortowane." << std::endl;
}

std::string PasswordManager::addSinglePasswordString() {
    std::string choice;
    std::string password;
    std::cout << "Czy chcesz wygenerowac haslo automatycznie? (t/n): ";
    std::cin >> choice;

    if (choice == "t") {
        int length;
        bool includeUppercase;
        bool includeLowercase;
        bool includeSpecialChars;

        std::cout << "Podaj dlugosc hasla: ";
        std::cin >> length;

        std::cout << "Czy haslo powinno zawierac wielkie litery? (t/n): ";
        std::cin >> choice;
        includeUppercase = (choice == "t");

        std::cout << "Czy haslo powinno zawierac male litery? (t/n): ";
        std::cin >> choice;
        includeLowercase = (choice == "t");

        std::cout << "Czy haslo powinno zawierac znaki specjalne? (t/n): ";
        std::cin >> choice;
        includeSpecialChars = (choice == "t");

        password = generatePassword(length, includeUppercase, includeLowercase, includeSpecialChars);
        std::cout << "Wygenerowane haslo to: " << password << std::endl;
    } else {
        std::cout << "Podaj haslo: ";
        std::cin >> password;
        if (isAlreadyUsed(passwordsString, password)) {
            std::cout << "Uzyles juz tego hasla, mozesz je zedytowac pozniej.\n";
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

    std::cout << "Podaj nazwe hasla: ";
    std::cin >> name;

    password = addSinglePasswordString();

    std::cout << "Podaj kategorie: ";
    std::cin >> category;

    std::cout << "Podaj strone WWW (opcjonalnie): ";
    std::cin >> website;

    std::cout << "Podaj login (opcjonalnie): ";
    std::cin >> login;

    Password newPassword;
    newPassword.name = name;
    newPassword.password = password;
    newPassword.category = category;
    newPassword.website = website;
    newPassword.login = login;

    passwords.push_back(newPassword);

    std::cout << "Haslo zostalo dodane." << std::endl;
}

void PasswordManager::editPassword() {
    std::string name;
    std::cout << "Podaj nazwę hasła do edycji: ";
    std::cin >> name;

    // Sprawdzenie, czy istnieje hasło o podanej nazwie
    bool passwordExists = false;
    for (Password& password : passwords) {
        if (password.name == name) {
            passwordExists = true;

            std::cout << "Wybierz pole do edycji: " << std::endl;
            std::cout << "1. Nazwa" << std::endl;
            std::cout << "2. Haslo" << std::endl;
            std::cout << "3. Kategoria" << std::endl;
            std::cout << "4. Strona WWW" << std::endl;
            std::cout << "5. Login" << std::endl;
            std::cout << "Wybierz opcje: ";
            std::string option;
            std::cin >> option;

            if (option == "1") {
                std::cout << "Podaj nowa nazwe: ";
                std::cin >> password.name;
                std::cout << "Nazwa zostala zaktualizowana." << std::endl;
            } else if (option == "2") {
                std::string newPassword;
                password.password = addSinglePasswordString();
                std::cout << "Haslo zostało zaktualizowane." << std::endl;
            } else if (option == "3") {
                std::cout << "Podaj nową kategorię: ";
                std::cin >> password.category;
                std::cout << "Kategoria została zaktualizowana." << std::endl;
            } else if (option == "4") {
                std::cout << "Podaj nowa stronę WWW: ";
                std::cin >> password.website;
                std::cout << "Strona WWW została zaktualizowana." << std::endl;
            } else if (option == "5") {
                std::cout << "Podaj nowy login: ";
                std::cin >> password.login;
                std::cout << "Login został zaktualizowany." << std::endl;
            } else {
                std::cout << "Nieprawidlowa opcja!" << std::endl;
            }
            break;
        }
    }

    if (!passwordExists) {
        std::cout << "Nie znaleziono hasła o podanej nazwie." << std::endl;
    }
}

void PasswordManager::deletePassword() {
    // Usuwanie wybranego hasła
}

void PasswordManager::manageCategories() {
    // Dodawanie i usuwanie kategorii
}

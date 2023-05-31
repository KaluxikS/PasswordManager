//
// Created by Piotr on 28.05.2023.
//

#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H


#include <string>
#include <vector>

struct Password {
    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;
};

class PasswordManager {
private:
    std::vector<Password> passwords;
    std::vector<std::string> passwordsString;
    std::string masterPassword;
    std::string filename;
    std::vector<std::string> categories;

public:
    PasswordManager(std::string masterPassword);

    void run();

private:
    void loadDataFromFile();
    void saveDataToFile();
    std::string encryptPassword(const Password& password);
    Password decryptPassword(const std::string& encryptedLine);
    std::string encrypt(std::string data);
    std::string decrypt(std::string encryptedData);
    std::string encryptTimestamp();
    void displayMenu();
    void processOption(const std::string& choice);
    void searchPasswords();
    void sortPasswords();
    void addPassword();
    void editPassword();
    void deletePassword();
    void addCategory();
    void removeCategory();
    void showCategory();
    void displayAllPasswords();
    bool isCategoryExists(const std::string& category);
    std::string addSinglePasswordString();
    bool isAlreadyUsed(const std::vector<std::string>& vec, const std::string& str);
    void isPasswordStrong(const std::string& password);
    std::string generatePassword(int length, bool includeUppercase, bool includeLowercase, bool includeSpecialChars);
    bool comparePasswords(const Password& password1, const Password& password2, const std::string& sortBy);
};

#endif // PASSWORD_MANAGER_H

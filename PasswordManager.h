//
// Created by Piotr on 28.05.2023.
//

#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H


#include <string>
#include <vector>

/**
 * @struct Password
 * @brief Represents a password that is saved to file with all it's fields.
 */

struct Password {
    std::string name; ///< Name of the password.
    std::string password; ///< Password as a string.
    std::string category; ///< Category of the password.
    std::string website; ///< The website, where the password is used.
    std::string login; ///< Login to the password.
};

/**
 * @class PasswordManager
 * @brief Manages the password and does various operation on them.
 */

class PasswordManager {
public:
    /**
     * @param masterPassword is used for the authentication.
     * @param filename name of file to load and save passwords
     */
    PasswordManager(std::string masterPassword, std::string filename);

    /**
     * @brief Runs the program.
     */
    void run();

private:
    std::vector<Password> passwords; ///< Vector of passwords used to save and load the line of file.
    std::vector<std::string> passwordsString; ///< Single password as a string.
    std::string masterPassword; ///< Is used for the authentication.
    std::string filename; ///< name of file to load and save passwords.
    std::vector<std::string> categories; ///< Vector of categories, used to manage the categories.

    /**
     * @brief Adds to logs unsuccessful attempt to access the password manager.
     */
    void logAttempt();

    /**
     * @brief Reads and prints logs from file.
     */
    void readLogFile();

    /**
     * @brief Loads data from file.
     */
    void loadDataFromFile();

    /**
     * @brief Saves data to file.
     */
    void saveDataToFile();

    /**
     * @brief Encrypts each object from vector into string line.
     * @param password Object to encrypt.
     * @return Encrypted string representation of each password (name, password etc.)
     */
    static std::string encryptPassword(const Password& password);

    /**
     * @brief Gets each line from file, separates fields.
     * @param encryptedLine Single line that represents structure of password.
     * @return Password structure that is ready to add to vector of passwords.
     */
    Password decryptPassword(const std::string& encryptedLine);

    /**
     * @brief Encrypts single string, with simple encryption algorithm.
     * @param data String to be encrypted.
     * @return Encrypted string.
     */
    static std::string encrypt(std::string data);

    /**
     * @brief Decrypts encrypted lines, with reverse of encryption algorithm.
     * @param encryptedData String that is encrypted.
     * @return Decrypted string
     */
    static std::string decrypt(std::string encryptedData);

    /**
     * @brief Displays the options from the menu.
     */
    static void displayMenu();

    /**
     * @brief Process the user's choice
     * @param choice User choice
     */
    void processOption(const std::string& choice);

    /**
     * @brief Displays all passwords stored in manager.
     */
    void displayAllPasswords();

    /**
     * @brief Checks if password is already used.
     * @param vec Vector of all passwords used.
     * @param str Password to check.
     * @return True if the password is used, otherwise false.
     */
    static bool isPasswordAlreadyUsed(const std::vector<std::string>& vec, const std::string& str);

    /**
     * @brief Checks if password is strong.
     * @param password Password to check.
     */
    static void isPasswordStrong(const std::string& password);

    /**
     * @brief Compares two passwords.
     * @param password1 First password to compare.
     * @param password2 Second password to compare.
     * @param sortBy Sorting parameter (name, category, website, login).
     * @return Returns true if password1 should be before password2.
     */
    static bool comparePasswords(const Password& password1, const Password& password2, const std::string& sortBy);

    /**
     * @brief Generates password based on parameters.
     * @param length Length of password.
     * @param includeUppercase True if password should include uppercase letters.
     * @param includeLowercase True if password should include lowercase letters.
     * @param includeSpecialChars True if password should include special characters.
     * @return Generated password.
     */
    static std::string generatePassword(int length, bool includeUppercase, bool includeLowercase, bool includeSpecialChars);

    /**
     * @brief Searches and prints password that matches to search parameter.
     */
    void searchPasswords();

    /**
     * @brief Sorts password by given sort parameter (name, category, website, login).
     */
    void sortPasswords();

    /**
     * @brief Adds string password to the manager.
     * @return The added password.
     */
    std::string addSinglePasswordString();

    /**
     * @brief Adds structure password to the manager.
     */
    void addPassword();

    /**
     * @brief Edits existing password in the manager.
     */
    void editPassword();

    /**
     * @brief Removes existing password in the manager.
     */
    void deletePassword();

    /**
     * @brief Adds category to the manager.
     */
    void addCategory();

    /**
     * @brief Removes category from the manager with all passwords connected to the category.
     */
    void removeCategory();

    /**
     * @brief Shows all categories in the password manager.
     */
    void showCategory();

    /**
     * @brief Checks if category exists in the manager.
     * @param category Category to check.
     * @return True if category exists, otherwise false.
     */
    bool isCategoryExists(const std::string& category);
};

#endif // PASSWORD_MANAGER_H

#include <iostream>
#include <string>
#include <unistd.h>  // crypt
#include <cstring>   // strcmp

// Function to hash a password using bcrypt
std::string hash_password(const std::string& password) {
    // 12 rounds, $2b$ indicates bcrypt version
    std::string salt = "$2b$12$1234567890123456789012"; // must be 22 chars after $2b$12$
    char* hashed = crypt(password.c_str(), salt.c_str());
    return std::string(hashed);
}

// Function to verify the password
bool verify_password(const std::string& password, const std::string& hashed) {
    char* check = crypt(password.c_str(), hashed.c_str());
    return std::strcmp(check, hashed.c_str()) == 0;
}

int main() {
    std::string password = "MySecurePassword";

    std::string hash = hash_password(password);
    std::cout << "Hashed password: " << hash << std::endl;

    std::string input;
    std::cout << "Enter password to verify: ";
    std::cin >> input;

    if (verify_password(input, hash)) {
        std::cout << "✅ Password verified!" << std::endl;
    } else {
        std::cout << "❌ Incorrect password." << std::endl;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

// Function to compute MD5 hash of a string
std::string md5(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), digest);

    std::ostringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];

    return ss.str();
}

int main() {
    std::string original_passcode = "Secret123";

    // Step 1: Hash the passcode
    std::string stored_hash = md5(original_passcode);
    std::cout << "Stored MD5 hash: " << stored_hash << std::endl;

    // Step 2: Ask user for input to verify
    std::string input_passcode;
    std::cout << "Enter passcode to verify: ";
    std::cin >> input_passcode;

    std::string input_hash = md5(input_passcode);

    // Step 3: Compare hashes
    if (input_hash == stored_hash) {
        std::cout << "✅ Passcode is correct!" << std::endl;
    } else {
        std::cout << "❌ Incorrect passcode." << std::endl;
    }

    return 0;
}

#include <iostream>
#include <chrono>
#include <jwt-cpp/jwt.h>

int main() {
    // Input values
    std::string service_name = "my_service";
    std::string api_key = "abc123xyz789";
    std::string secret = "my_super_secret_key"; // HMAC secret

    // Current timestamp
    auto now = std::chrono::system_clock::now();
    auto now_sec = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    // Create JWT token
    auto token = jwt::create()
        .set_issuer("certifyme")
        .set_type("JWT")
        .set_payload_claim("service", jwt::claim(service_name))
        .set_payload_claim("api_key", jwt::claim(api_key))
        .set_payload_claim("timestamp", jwt::claim(std::to_string(now_sec)))
        .set_issued_at(now_sec)
        .set_expires_at(now_sec + 3600) // 1 hour validity
        .sign(jwt::algorithm::hs256{secret});

    std::cout << "Generated JWT:\n" << token << std::endl;

    return 0;
}

vcpkg install jwt-cpp nlohmann-json openssl


g++ jwt_gen.cpp -o jwt_gen -I/path/to/vcpkg/installed/x64-linux/include -L/path/to/vcpkg/installed/x64-linux/lib -lssl -lcrypto

sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

g++ aes256_example.cpp -o aes256_example -lcryptopp
./aes256_example
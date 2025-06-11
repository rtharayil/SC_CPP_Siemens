sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils



g++ rsa_sign_verify.cpp -o rsa_sign_verify -lcryptopp
./rsa_sign_verify




g++ rsa_key_io.cpp -o rsa_key_io -lcryptopp
./rsa_key_io
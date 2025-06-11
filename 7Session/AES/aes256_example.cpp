#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

int main() {
    AutoSeededRandomPool prng;

    // 256-bit key (32 bytes) and 128-bit IV (16 bytes)
    SecByteBlock key(AES::DEFAULT_KEYLENGTH * 2); // AES-256
    SecByteBlock iv(AES::BLOCKSIZE);

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::string plaintext = "Secret message that needs encryption";
    std::string ciphertext, decryptedtext;

    // Encryption
    CBC_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    StringSource ss1(plaintext, true,
        new StreamTransformationFilter(encryptor,
            new StringSink(ciphertext)
        )
    );

    // Decryption
    CBC_Mode<AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), iv);

    StringSource ss2(ciphertext, true,
        new StreamTransformationFilter(decryptor,
            new StringSink(decryptedtext)
        )
    );

    // Print results
    std::cout << "Original Text: " << plaintext << std::endl;

    // Hex-encode ciphertext for readable output
    std::string encoded;
    StringSource(ciphertext, true, new HexEncoder(new StringSink(encoded)));
    std::cout << "Encrypted (hex): " << encoded << std::endl;

    std::cout << "Decrypted Text: " << decryptedtext << std::endl;

    return 0;
}

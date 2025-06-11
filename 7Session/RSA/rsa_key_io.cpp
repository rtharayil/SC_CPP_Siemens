#include <iostream>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/files.h>
#include <cryptopp/base64.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

// Save a key to a file in Base64 format
template<typename T>
void SaveKey(const std::string& filename, const T& key) {
    Base64Encoder encoder(new FileSink(filename.c_str()));
    key.DEREncode(encoder);
    encoder.MessageEnd();
}

// Load a key from a Base64-encoded file
template<typename T>
void LoadKey(const std::string& filename, T& key) {
    FileSource file(filename.c_str(), true, new Base64Decoder);
    key.BERDecode(file);
}

int main() {
    AutoSeededRandomPool rng;

    // 1. Generate RSA key pair
    InvertibleRSAFunction params;
    params.Initialize(rng, 2048);

    RSA::PrivateKey privateKey(params);
    RSA::PublicKey publicKey(params);

    // 2. Save keys to files
    SaveKey("rsa-private.key", privateKey);
    SaveKey("rsa-public.key", publicKey);
    std::cout << "🔐 Keys saved to 'rsa-private.key' and 'rsa-public.key'\n";

    // 3. Load keys back from files
    RSA::PrivateKey loadedPrivateKey;
    RSA::PublicKey loadedPublicKey;

    LoadKey("rsa-private.key", loadedPrivateKey);
    LoadKey("rsa-public.key", loadedPublicKey);
    std::cout << "✅ Keys loaded back successfully\n";

    // Test: Encrypt and Decrypt using loaded keys
    std::string message = "This is a test message!";
    std::string encrypted, decrypted;

    RSAES_OAEP_SHA_Encryptor encryptor(loadedPublicKey);
    StringSource(message, true, new PK_EncryptorFilter(rng, encryptor, new StringSink(encrypted)));

    RSAES_OAEP_SHA_Decryptor decryptor(loadedPrivateKey);
    StringSource(encrypted, true, new PK_DecryptorFilter(rng, decryptor, new StringSink(decrypted)));

    std::cout << "🔒 Encrypted and Decrypted successfully: " << decrypted << std::endl;
    return 0;
}

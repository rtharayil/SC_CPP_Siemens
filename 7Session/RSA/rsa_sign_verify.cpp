#include <iostream>
#include <string>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/sha.h>
#include <cryptopp/pssr.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

using namespace CryptoPP;

int main() {
    AutoSeededRandomPool prng;

    // Generate RSA keys
    InvertibleRSAFunction privateKeyParams;
    privateKeyParams.Initialize(prng, 2048);
    RSA::PrivateKey privateKey(privateKeyParams);
    RSA::PublicKey publicKey(privateKeyParams);

    // Message to be signed
    std::string message = "Confidential message for signing.";
    std::string signature;

    // Sign the message with RSA + SHA256 + PSS
    try {
        RSASS<PSS, SHA256>::Signer signer(privateKey);

        StringSource ss1(message, true,
            new SignerFilter(prng, signer,
                new StringSink(signature)
            )
        );

        std::cout << "✅ Signature created successfully." << std::endl;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Signing failed: " << e.what() << std::endl;
        return 1;
    }

    // Verify the signature
    bool result = false;
    try {
        RSASS<PSS, SHA256>::Verifier verifier(publicKey);

        StringSource ss2(message + signature, true,
            new SignatureVerificationFilter(
                verifier,
                new ArraySink((byte*)&result, sizeof(result)),
                SignatureVerificationFilter::PUT_RESULT | SignatureVerificationFilter::SIGNATURE_AT_END
            )
        );

        if (result)
            std::cout << "✅ Signature verification passed." << std::endl;
        else
            std::cout << "❌ Signature verification failed!" << std::endl;

    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Verification failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

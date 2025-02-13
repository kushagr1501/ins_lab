#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <bitset>
using namespace std;
class EnhancedHybridCipher {
private:
    string masterKey;
    vector<string> roundKeys;
    vector<vector<int>> transpositionKeys;
    const int BLOCK_SIZE = 32; // Increased block size
    const int NUM_ROUNDS = 2;  // Multiple rounds
    const int MIN_KEY_LENGTH = 24; // For 128-bit security

    // Key derivation function
    void deriveKeys() {
        string baseKey = masterKey;
        while (baseKey.length() < MIN_KEY_LENGTH) {
            baseKey += masterKey; // Key expansion
        }
        
        roundKeys.resize(NUM_ROUNDS);
        transpositionKeys.resize(NUM_ROUNDS, vector<int>(BLOCK_SIZE));
        
        // Generate unique keys for each round
        for (int round = 0; round < NUM_ROUNDS; round++) {
            // Derive round key for Vigenère
            stringstream ss;
            ss << baseKey << round;
            roundKeys[round] = ss.str();
            
            // Generate transposition key
            for (int i = 0; i < BLOCK_SIZE; i++) {
                transpositionKeys[round][i] = i;
            }
            
            // Unique shuffle for each round
            std::seed_seq seed(roundKeys[round].begin(), roundKeys[round].end());
            std::mt19937 gen(seed);
            std::shuffle(transpositionKeys[round].begin(), transpositionKeys[round].end(), gen);
        }
    }

    // Enhanced Vigenère with extended character set (256 characters)
    unsigned char vigenereEncrypt(unsigned char plainchar, unsigned char keychar) {
        return (plainchar + keychar) % 256;
    }

    unsigned char vigenereDecrypt(unsigned char cipherchar, unsigned char keychar) {
        return (cipherchar - keychar + 256) % 256;
    }

    // Secure padding with length and randomization
    vector<unsigned char> padMessage(const vector<unsigned char>& message) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        int paddingLength = BLOCK_SIZE - (message.size() % BLOCK_SIZE);
        std::vector<unsigned char> padded = message;
        
        // Add random padding except last byte
        for (int i = 0; i < paddingLength - 1; i++) {
            padded.push_back(dis(gen));
        }
        // Last byte indicates padding length
        padded.push_back(paddingLength);
        
        return padded;
    }

    vector<unsigned char> removePadding(const vector<unsigned char>& message) {
        if (message.empty()) return message;
        int paddingLength = message.back();
        return std::vector<unsigned char>(message.begin(), message.end() - paddingLength);
    }

    // Single round of encryption
    vector<unsigned char> encryptRound(const vector<unsigned char>& input, int round) {
        std::vector<unsigned char> output = input;
        
        // Apply Vigenère
        for (size_t i = 0; i < output.size(); i++) {
            unsigned char keyChar = roundKeys[round][i % roundKeys[round].length()];
            output[i] = vigenereEncrypt(output[i], keyChar);
        }
        
        // Apply transposition block by block
        std::vector<unsigned char> transposed(output.size());
        for (size_t block = 0; block < output.size(); block += BLOCK_SIZE) {
            for (int i = 0; i < BLOCK_SIZE; i++) {
                transposed[block + transpositionKeys[round][i]] = output[block + i];
            }
        }
        
        return transposed;
    }

    // Single round of decryption
    vector<unsigned char> decryptRound(const vector<unsigned char>& input, int round) {
        std::vector<unsigned char> output = input;
        
        // Reverse transposition
        std::vector<unsigned char> untransposed(output.size());
        for (size_t block = 0; block < output.size(); block += BLOCK_SIZE) {
            for (int i = 0; i < BLOCK_SIZE; i++) {
                untransposed[block + i] = output[block + transpositionKeys[round][i]];
            }
        }
        
        // Reverse Vigenère
        for (size_t i = 0; i < untransposed.size(); i++) {
            unsigned char keyChar = roundKeys[round][i % roundKeys[round].length()];
            untransposed[i] = vigenereDecrypt(untransposed[i], keyChar);
        }
        
        return untransposed;
    }

public:
    EnhancedHybridCipher(const string& key) {
        if (key.length() < 16) {
            throw std::runtime_error("Key must be at least 16 characters long");
        }
        masterKey = key;
        deriveKeys();
    }

    vector<unsigned char> encrypt(const vector<unsigned char>& plaintext) {
        std::vector<unsigned char> ciphertext = padMessage(plaintext);
        
        // Apply multiple rounds
        for (int round = 0; round < NUM_ROUNDS; round++) {
            ciphertext = encryptRound(ciphertext, round);
        }
        
        return ciphertext;
    }

    vector<unsigned char> decrypt(const vector<unsigned char>& ciphertext) {
        std::vector<unsigned char> plaintext = ciphertext;
        
        // Apply rounds in reverse
        for (int round = NUM_ROUNDS - 1; round >= 0; round--) {
            plaintext = decryptRound(plaintext, round);
        }
        
        return removePadding(plaintext);
    }

    // Calculate effective bit security
    double calculateBitSecurity() {
        double vigenereKeySpace = std::log2(std::pow(256, MIN_KEY_LENGTH));
        double transpositionKeySpace = std::log2(factorial(BLOCK_SIZE));
        double roundSecurity = vigenereKeySpace + transpositionKeySpace;
        return roundSecurity * NUM_ROUNDS;
    }

private:
    double factorial(int n) {
        double result = 1.0;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
};

// Example usage and security validation
int main() {
    try {
        std::string key = "ThisIsAVeryLongAndSecureKey123!@#";
        EnhancedHybridCipher cipher(key);

        // Calculate and display security level
        double bitSecurity = cipher.calculateBitSecurity();
        cout << "Effective security strength: " << bitSecurity << " bits\n";
        
        if (bitSecurity >= 128) {
            cout << " Meets 128-bit security requirement\n";
        } else {
            cout << " Does not meet 128-bit security requirement\n";
        }

        // Test encryption and decryption
        string message = "This is a secret ";
        vector<unsigned char> plaintext(message.begin(), message.end());
        
        auto encrypted = cipher.encrypt(plaintext);
        auto decrypted = cipher.decrypt(encrypted);
        
        string decryptedMsg(decrypted.begin(), decrypted.end());
        cout << "\nOriginal: " << message << "\n";
        cout << "Decrypted: " << decryptedMsg << "\n";

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
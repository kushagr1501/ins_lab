#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// Secure random number generation
class SecureRandom {
private:
    random_device rd;
    mt19937_64 gen;
    
public:
    SecureRandom() : gen(rd()) {}
    
    string generateKey(size_t length) {
        uniform_int_distribution<> dis(0, 255);
        string key;
        for (size_t i = 0; i < length; i++) {
            key += static_cast<char>(dis(gen));
        }
        return key;
    }
};

class EnhancedVigenereCipher {
private:
    string key;
    
    uint8_t shiftByte(uint8_t b, uint8_t k, bool encrypt) {
        int shift = (encrypt ? 1 : -1) * k;
        return static_cast<uint8_t>((b + shift + 256) % 256);
    }

public:
    EnhancedVigenereCipher(const string &key) : key(key) {}
    
    string encrypt(const string &data) {
        string ciphertext;
        size_t j = 0;
        for (size_t i = 0; i < data.length(); i++) {
            ciphertext += shiftByte(data[i], key[j], true);
            j = (j + 1) % key.length();
        }
        return ciphertext;
    }

    string decrypt(const string &data) {
        string plaintext;
        size_t j = 0;
        for (size_t i = 0; i < data.length(); i++) {
            plaintext += shiftByte(data[i], key[j], false);
            j = (j + 1) % key.length();
        }
        return plaintext;
    }
};

class EnhancedColumnarTransposition {
private:
    string key;
    
    vector<int> getKeyOrder() {
        vector<pair<unsigned char, int>> keyOrder;
        for (size_t i = 0; i < key.length(); i++) {
            keyOrder.emplace_back(key[i], i);
        }
        sort(keyOrder.begin(), keyOrder.end());
        
        vector<int> order(key.length());
        for (size_t i = 0; i < keyOrder.size(); i++) {
            order[keyOrder[i].second] = i;
        }
        return order;
    }

public:
    EnhancedColumnarTransposition(const string &key) : key(key) {}
    
    string encrypt(const string &data) {
        int cols = key.length();
        int rows = (data.length() + cols - 1) / cols;
        
        vector<vector<unsigned char>> grid(rows, vector<unsigned char>(cols, 0));
        
        int index = 0;
        for (int r = 0; r < rows && index < data.length(); r++) {
            for (int c = 0; c < cols && index < data.length(); c++) {
                grid[r][c] = data[index++];
            }
        }
        
        vector<int> order = getKeyOrder();
        
        string ciphertext;
        for (int c : order) {
            for (int r = 0; r < rows; r++) {
                ciphertext += grid[r][c];
            }
        }
        
        // Add length as 64-bit value
        uint64_t len = data.length();
        for (int i = 0; i < 8; i++) {
            ciphertext += static_cast<char>((len >> (i * 8)) & 0xFF);
        }
        
        return ciphertext;
    }

    string decrypt(const string &data) {
        if (data.length() < 8) return "";
        
        // Extract original length from last 8 bytes
        uint64_t originalLength = 0;    
        for (int i = 0; i < 8; i++) {
            originalLength |= static_cast<uint64_t>(static_cast<unsigned char>(data[data.length() - 8 + i])) << (i * 8);
        }
        
        string actualData = data.substr(0, data.length() - 8);
        
        int cols = key.length();
        int rows = (actualData.length() + cols - 1) / cols;
        
        vector<vector<unsigned char>> grid(rows, vector<unsigned char>(cols));
        vector<int> order = getKeyOrder();
        
        int index = 0;
        for (int c : order) {
            for (int r = 0; r < rows && index < actualData.length(); r++) {
                grid[r][c] = actualData[index++];
            }
        }
        
        string plaintext;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                plaintext += grid[r][c];
            }
        }
        
        return plaintext.substr(0, originalLength);
    }
};

class EnhancedHybridCipher {
private:
    EnhancedVigenereCipher vigenere;
    EnhancedColumnarTransposition transposition;
    
public:
    EnhancedHybridCipher(const string &vigenereKey, const string &transpositionKey)
        : vigenere(vigenereKey), transposition(transpositionKey) {}
    
    static pair<string, string> generateKeys() {
        SecureRandom rng;
        string vigenereKey = rng.generateKey(32);      // 256-bit key
        string transpositionKey = rng.generateKey(16); // 128-bit key
        return {vigenereKey, transpositionKey};
    }
    
    string encrypt(const string &plaintext) {
        string step1 = vigenere.encrypt(plaintext);
        return transposition.encrypt(step1);
    }
    
    string decrypt(const string &ciphertext) {
        string step1 = transposition.decrypt(ciphertext);
        return vigenere.decrypt(step1);
    }
    
    // Utility function to convert binary string to hex for display
    static string toHex(const string &input) {
        stringstream ss;
        ss << hex << setfill('0');
        for (unsigned char c : input) {
            ss << setw(2) << static_cast<int>(c);
        }
        return ss.str();
    }
};
int main() {
    // Generate secure random keys
    std::pair<string, string> keys = EnhancedHybridCipher::generateKeys();
    string vigenereKey = keys.first;
    string transpositionKey = keys.second;
    
    cout << "Generated Keys (hex):" << endl;
    cout << "Vigenere Key: " << EnhancedHybridCipher::toHex(vigenereKey) << endl;
    cout << "Transposition Key: " << EnhancedHybridCipher::toHex(transpositionKey) << endl;
    
    EnhancedHybridCipher hybrid(vigenereKey, transpositionKey);
    
    string message = "This is a secret message that needs strong encryption!";
    cout << "\nOriginal: " << message << endl;
    
    string encrypted = hybrid.encrypt(message);
    cout << "Encrypted (hex): " << EnhancedHybridCipher::toHex(encrypted) << endl;
    
    string decrypted = hybrid.decrypt(encrypted);
    cout << "Decrypted: " << decrypted << endl;
    
    if (message == decrypted) {
        cout << "\nSuccess: Decryption matches original text!" << endl;
    } else {
        cout << "\nError: Decryption does not match original text!" << endl;
    }
    
    return 0;
}

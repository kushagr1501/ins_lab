#include<bits/stdc++.h>
using namespace std;

// ========================== Vigenere Cipher ==========================
class VigenereCipher {
private:
    string key;
    
    char shiftChar(char c, char k, bool encrypt) {
        int shift = (encrypt ? 1 : -1) * (toupper(k) - 'A');
        return 'A' + (toupper(c) - 'A' + shift + 26) % 26;
    }

public:
    VigenereCipher(const string &key) : key(key) {}

    string encrypt(const string &text) {
        string ciphertext;
        for (size_t i = 0, j = 0; i < text.length(); i++) {
            if (isalpha(text[i])) {
                ciphertext += shiftChar(text[i], key[j], true);
                j = (j + 1) % key.length();
            } else {
                ciphertext += text[i]; 
            }
        }
        return ciphertext;
    }

    string decrypt(const string &text) {
        string plaintext;
        for (size_t i = 0, j = 0; i < text.length(); i++) {
            if (isalpha(text[i])) {
                plaintext += shiftChar(text[i], key[j], false);
                j = (j + 1) % key.length();
            } else {
                plaintext += text[i];
            }
        }
        return plaintext;
    }
};

// ========================== Columnar Transposition Cipher ==========================
class ColumnarTranspositionCipher {
private:
    string key;

    vector<int> getKeyOrder() {
        vector<pair<char, int>> keyOrder;
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
    ColumnarTranspositionCipher(const string &key) : key(key) {}

    string encrypt(const string &plaintext) {
        int cols = key.length();
        int rows = (plaintext.length() + cols - 1) / cols;
        vector<vector<char>> grid(rows, vector<char>(cols, 'X'));

        int index = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols && index < plaintext.length(); c++) {
                grid[r][c] = plaintext[index++];
            }
        }

        vector<int> order = getKeyOrder();
        string ciphertext;
        for (int c : order) {
            for (int r = 0; r < rows; r++) {
                ciphertext += grid[r][c];
            }
        }
        return ciphertext;
    }

    string decrypt(const string &ciphertext) {
        int cols = key.length();
        int rows = (ciphertext.length() + cols - 1) / cols;
        vector<vector<char>> grid(rows, vector<char>(cols, 'X'));

        vector<int> order = getKeyOrder();
        int index = 0;
        for (int c : order) {
            for (int r = 0; r < rows; r++) {
                if (index < ciphertext.length()) {
                    grid[r][c] = ciphertext[index++];
                }
            }
        }

        string plaintext;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                plaintext += grid[r][c];
            }
        }

        // Remove extra padding (trailing Xs)
        while (!plaintext.empty() && plaintext.back() == 'X') {
            plaintext.pop_back();
        }

        return plaintext;
    }
};

// ========================== Hybrid Cipher ==========================
class HybridCipher {
private:
    VigenereCipher vigenere;
    ColumnarTranspositionCipher transposition;

public:
    HybridCipher(const string &vigenereKey, const string &transpositionKey)
        : vigenere(vigenereKey), transposition(transpositionKey) {}

    string encrypt(const string &plaintext) {
        string step1 = vigenere.encrypt(plaintext);
        return transposition.encrypt(step1);
    }

    string decrypt(const string &ciphertext) {
        string step1 = transposition.decrypt(ciphertext);
        return vigenere.decrypt(step1);
    }
};

int main() {
    string vigenereKey = "KEY";
    string transpositionKey = "SECURE";

    HybridCipher hybrid(vigenereKey, transpositionKey);

    string message = "HELLO THIS IS A HYBRID CIPHER HEHEHEHE";
    cout << "Original: " << message << endl;

    string encrypted = hybrid.encrypt(message);
    cout << "Encrypted: " << encrypted << endl;

    string decrypted = hybrid.decrypt(encrypted);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}

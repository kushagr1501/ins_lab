#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <random>

using namespace std;

// Function to convert string to binary string
string stringToBinary(const string &s) {
    string binaryString = "";
    for (char c : s) {
        binaryString += bitset<8>(c).to_string();
    }
    return binaryString;
}

// Function to shift and generate keys (basic simulation like your Python logic)
vector<string> generateKeys(string left, string right, vector<int> lt) {
    vector<string> keys;
    for (int i = 0; i < 8; i++) {
        string newKey = "";

        // Convert to int, shift, convert back to binary
        int nl = stoi(left, 0, 2);
        nl = nl << lt[i];
        string shiftedLeft = bitset<32>(nl).to_string();  // 32-bit to handle shifts

        int nr = stoi(right, 0, 2);
        nr = nr << lt[i];
        string shiftedRight = bitset<32>(nr).to_string();

        // Combine left and right (simulated circular shift)
        newKey = shiftedRight.substr(32-lt[i]) + shiftedLeft.substr(32-lt[i]);

        // Random removal of 8 bits (simulate part of your Python logic)
        vector<int> rm;
        while (rm.size() < 8) {
            int r = rand() % newKey.size();
            if (find(rm.begin(), rm.end(), r) == rm.end()) {
                rm.push_back(r);
            }
        }

        string newAnswer = "";
        for (int j = 0; j < newKey.size(); j++) {
            if (find(rm.begin(), rm.end(), j) == rm.end()) {
                newAnswer += newKey[j];
            }
        }

        keys.push_back(newAnswer);
    }
    return keys;
}

// Function to "decrypt" (reverse shifts to recover original binary)
string decryptWithKeys(string left, string right, vector<int> lt, const vector<string>& keys) {
    for (int i = 0; i < 8; i++) {
        int nl = stoi(left, 0, 2);
        nl = nl >> lt[i];  // Reverse shift left side

        int nr = stoi(right, 0, 2);
        nr = nr >> lt[i];  // Reverse shift right side

        left = bitset<16>(nl).to_string();   // Shorten for simplicity
        right = bitset<16>(nr).to_string();
    }
    return left + right;
}

// Main encryption/decryption driver
int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    string binaryString = stringToBinary(input);
    cout << "Binary: " << binaryString << endl;

    int half = binaryString.size() / 2;
    string left = binaryString.substr(0, half);
    string right = binaryString.substr(half);

    vector<int> lt = {2, 3, 6, 7, 1, 6, 5, 9};  // Shift values

    vector<string> keys = generateKeys(left, right, lt);

    cout << "\nGenerated Keys:\n";
    for (int i = 0; i < keys.size(); i++) {
        cout << "Key " << (i+1) << " = " << keys[i] << endl;
    }

    // For simplicity, directly recover (inverse of shift logic)
    string decryptedBinary = decryptWithKeys(left, right, lt, keys);
    cout << "\nDecrypted Binary (recovered): " << decryptedBinary << endl;

    // Convert binary back to text (basic simulation)
    string recoveredText = "";
    for (size_t i = 0; i < decryptedBinary.size(); i += 8) {
        bitset<8> charBits(decryptedBinary.substr(i, 8));
        recoveredText += char(charBits.to_ulong());
    }

    cout << "Recovered Text: " << recoveredText << endl;

    return 0;
}

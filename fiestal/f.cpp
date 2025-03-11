#include <iostream>
#include <string>
#include <bitset>

using namespace std;

// Convert string to binary string
string toBinaryString(const string &s) {
    string binary = "";
    for (char c : s) {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}

// Convert binary string back to ASCII string
string binaryToString(const string &binary) {
    string result = "";
    for (size_t i = 0; i < binary.size(); i += 8) {
        string byte = binary.substr(i, 8);
        char c = static_cast<char>(bitset<8>(byte).to_ulong());
        result += c;
    }
    return result;
}

string padToLength(const string &input, size_t length) {
    string padded = input;
    while (padded.size() < length) {
        padded = "0" + padded;
    }
    return padded;
}

int main() {
    string s, k;
    cout << "Enter a string: ";
    getline(cin, s);

    // Convert string to binary
    string result = toBinaryString(s);
    cout << "Result: " << result << endl;

    int l = result.size() / 2;
    string left = result.substr(0, l);
    string right = result.substr(l);

    cout << "Enter a key: ";
    getline(cin, k);
    string key = toBinaryString(k);

    // Convert parts and key to integer
    unsigned long rightInt = bitset<64>(right).to_ulong();
    unsigned long keyInt = bitset<64>(key).to_ulong();
    unsigned long leftInt = bitset<64>(left).to_ulong();

    // First round of Feistel process
    unsigned long sum = rightInt + keyInt;
    unsigned long answer = sum ^ leftInt;

    string newr = bitset<64>(answer).to_string();
    string newl = right;

    // Swap left and right
    swap(newr, newl);

    // Second round
    rightInt = bitset<64>(newr).to_ulong();
    sum = rightInt + keyInt;
    unsigned long ans = sum ^ bitset<64>(newl).to_ulong();

    string nl = newr;
    string nr = bitset<64>(ans).to_string();

    // Swap again
    swap(nl, nr);

    string cipher = nl + nr;

    // Ensure cipher length matches original binary length
    if (cipher.size() != result.size()) {
        cipher = padToLength(cipher, result.size());
    }

    cout << "Cipher: " << cipher << endl;

    // Convert binary cipher back to plaintext
    string plainText = binaryToString(cipher);
    cout << "Plaintext: " << plainText << endl;

    return 0;
}

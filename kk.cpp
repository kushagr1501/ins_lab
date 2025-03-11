#include <iostream>
#include <string>
#include <bitset>
#include <vector>

// Function to convert a string to binary string
std::string stringToBinary(const std::string& str) {
    std::string binary = "";
    for (char c : str) {
        binary += std::bitset<8>(c).to_string();
    }
    return binary;
}

// Function to convert binary string to ASCII string
std::string binaryToString(const std::string& binary) {
    std::string text = "";
    for (size_t i = 0; i < binary.length(); i += 8) {
        std::string byte = binary.substr(i, 8);
        char c = static_cast<char>(std::bitset<8>(byte).to_ulong());
        text += c;
    }
    return text;
}

int main() {
    // Get input string
    std::string s;
    std::cout << "Enter a string : ";
    std::getline(std::cin, s);
    
    // Convert string to binary
    std::string result = stringToBinary(s);
    std::cout << "Result : " << result << std::endl;
    
    // Split into left and right halves
    int l = result.length() / 2;
    std::string left = result.substr(0, l);
    std::string right = result.substr(l);
    
    // Get key
    std::string k;
    std::cout << "Enter a key : ";
    std::getline(std::cin, k);
    
    // Convert key to binary
    std::string key = stringToBinary(k);
    
    // First round
    // Add right half and key
    unsigned long long rightInt = std::stoull(right, nullptr, 2);
    unsigned long long keyInt = std::stoull(key, nullptr, 2);
    std::string s_bin = std::bitset<64>(rightInt + keyInt).to_string();
    
    // Remove leading zeros
    s_bin = s_bin.substr(s_bin.find('1'));
    
    // XOR with left half
    unsigned long long leftInt = std::stoull(left, nullptr, 2);
    unsigned long long answerInt = std::stoull(s_bin, nullptr, 2) ^ leftInt;
    std::string answer = std::bitset<64>(answerInt).to_string();
    
    // Remove leading zeros
    answer = answer.substr(answer.find('1'));
    
    // Swap left and right
    std::string newr = right;
    std::string newl = answer;
    
    // Second round
    std::swap(newr, newl);
    
    // Add new right and key
    rightInt = std::stoull(newr, nullptr, 2);
    s_bin = std::bitset<64>(rightInt + keyInt).to_string();
    
    // Remove leading zeros
    s_bin = s_bin.substr(s_bin.find('1'));
    
    // XOR with new left
    leftInt = std::stoull(newl, nullptr, 2);
    answerInt = std::stoull(s_bin, nullptr, 2) ^ leftInt;
    answer = std::bitset<64>(answerInt).to_string();
    
    // Remove leading zeros
    answer = answer.substr(answer.find('1'));
    
    // Swap again
    std::string nl = newr;
    std::string nr = answer;
    std::swap(nl, nr);
    
    // Combine to get cipher
    std::string cipher = nl + nr;
    
    // Ensure cipher has correct length by adding leading zeros if needed
    if (cipher.length() != result.length()) {
        while (cipher.length() < result.length()) {
            cipher = "0" + cipher;
        }
    }
    
    std::cout << "Cipher: " << cipher << std::endl;
    
    // Convert binary cipher to plaintext
    std::string plainText = binaryToString(cipher);
    std::cout << "Plaintext: " << plainText << std::endl;
    
    return 0;
}
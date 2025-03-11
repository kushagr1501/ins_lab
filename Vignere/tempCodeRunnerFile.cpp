#include <bits/stdc++.h>
using namespace std;

string cleanString(string &str)
{
    string result;
    for (char c : str)
    {
        if(isalpha(c))
        result += toupper(c);
    }
    return result;
}

//  encrypt 
string encrypt(string &message,  string &key)
{
 
    string newMessage = cleanString(message);
    string newKey = cleanString(key);

    string encrypted;
    int keyLength = newKey.length();

    for (int i = 0; i < newMessage.length(); i++)
    {

        char messageChar = newMessage[i];
        char keyChar = newKey[i % keyLength];

        int messageNum = messageChar - 'A';
        int keyNum = keyChar - 'A';

        int encryptedNum = (messageNum + keyNum) % 26;

        encrypted += (char)(encryptedNum + 'A');
    }

    return encrypted;
}

//  decrypt a message
string decrypt(string &encryptedMessage,  string &key)
{
    string Encrypted = cleanString(encryptedMessage);
    string Key = cleanString(key);

    string decrypted;
    int keyLength = Key.length();

    for (int i = 0; i < Encrypted.length(); i++)
    {
        char encryptedChar = Encrypted[i];
        char keyChar = Key[i % keyLength];

        int encryptedNum = encryptedChar - 'A';
        int keyNum = keyChar - 'A';

        int decryptedNum = (encryptedNum - keyNum + 26) % 26; // Added  26 to handle negative numbers

        decrypted += (char)(decryptedNum + 'A');
    }

    return decrypted;
}

int main()
{
    string message = "HELLO  WORLD";
    string key = "KEY";

    // Encrypt the message
    string encrypted = encrypt(message, key);
    cout << "Encrypted message: " << encrypted << endl;

    // Decrypt the message
    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted message: " << decrypted << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

vector<int> multi(vector<vector<int>> &key, vector<int> &block) {
    vector<int> res(block.size(), 0);
    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < block.size(); j++) {
            res[i] += key[i][j] * block[j];
        }
        res[i] %= 26; // Modulo 26
    }
    return res;
}

string fn(vector<vector<int>> &key, string plaintext) {
    int n = key.size(); // Size of key matrix
    string cipar = "";

    // Convert to uppercase
    for (auto &ch : plaintext) {
        if (ch >= 'a' && ch <= 'z') {
            ch = toupper(ch);
        }
    }

  
    while (plaintext.length() % n != 0) {
        plaintext += 'X'; // Padding with 'X'
    }

    // Encryption
    for (int i = 0; i < plaintext.length(); i += n) {
        vector<int> block(n);
        for (int j = 0; j < n; j++) {
            block[j] = plaintext[i + j] - 'A'; 
        }

        vector<int> res = multi(key, block);
        for (auto num : res) {
            cipar += (num + 'A'); 
        }
    }

    return cipar;
}

int main() {
    vector<vector<int>> key = {{6, 24}, {1, 13}}; 
    string plaintext = "HELLO";

    string encrypted = fn(key, plaintext);
    cout << "Encrypted text: " << encrypted << endl;

    return 0;
}




int determinant(const vector<vector<int>>& key) {
    return ((key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26 + 26) % 26;
}

int modInverse(int a) {
    a = a % 26;
    for (int x = 1; x < 26; x++)
        if ((a * x) % 26 == 1)
            return x;
    return 1;
}

vector<vector<int>> adjoint(const vector<vector<int>>& key) {
    return {
        {key[1][1], (-key[0][1] + 26) % 26},
        {(-key[1][0] + 26) % 26, key[0][0]}
    };
}

    string decrypt(const vector<vector<int>>& key, string ciphertext) {

    int det = determinant(key);
        int detInv = modInverse(det);
        vector<vector<int>> adj = adjoint(key);
        
        vector<vector<int>> invKey(2, vector<int>(2));
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                invKey[i][j] = (adj[i][j] * detInv) % 26;
            }
        }

    string plaintext;
        for(int i = 0; i < ciphertext.length(); i += 2) {

    vector<int> block = {
                ciphertext[i] - 'A',
                ciphertext[i + 1] - 'A'
            };

    vector<int> result(2);
            for(int i = 0; i < 2; i++) {
                result[i] = 0;
                for(int j = 0; j < 2; j++) {
                    result[i] += invKey[i][j] * block[j];
                }
                result[i] = ((result[i] % 26) + 26) % 26;
            }

    plaintext += (result[0] + 'A');
            plaintext += (result[1] + 'A');
        }
        
        return plaintext;
    }
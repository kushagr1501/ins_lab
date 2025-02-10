#include <bits/stdc++.h>
using namespace std;

class PlayfairCipher
{
private:
    char matrix[5][5];

    void createMatrix(string key)
    {

        for (int i = 0; i < key.length(); i++)
        {
            key[i] = toupper(key[i]);
            if (key[i] == 'J')
                key[i] = 'I';
        }

        //  boolean array to track used letters
        bool used[26] = {false};

        int row = 0, col = 0;

        // First, place the key letters
        for (char c : key)
        {
            if (!used[c - 'A'] && c != 'J')
            {
                matrix[row][col] = c;
                used[c - 'A'] = true;
                col++;
                if (col == 5)
                {
                    col = 0;
                    row++;
                }
            }
        }

        for (char c = 'A'; c <= 'Z'; c++)
        {
            if (!used[c - 'A'] && c != 'J')
            {
                matrix[row][col] = c;
                col++;
                if (col == 5)
                {
                    col = 0;
                    row++;
                }
            }
        }
    }

    pair<int, int> findPosition(char c)
    {
        if (c == 'J')
            c = 'I';
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (matrix[i][j] == c)
                    return {i, j};
        return {-1, -1};
    }

public:
    PlayfairCipher(string key)
    {
        createMatrix(key);
    }

    string encrypt(string text)
    {

        string temp = "";
        for (char c : text)
        {
            if (isalpha(c))
            {
                temp += toupper(c);
                if (temp.back() == 'J')
                    temp.back() = 'I';
            }
        }
        text = temp;

        for (size_t i = 0; i < text.length(); i += 2)
        {
            if (i + 1 == text.length())
            {
                text += 'X';
            }
            else if (text[i] == text[i + 1])
            {
                text.insert(i + 1, "X");
            }
        }

        // Encrypt the digraphs
        string result = "";
        for (int i = 0; i < text.length(); i += 2)
        {
            char c1 = text[i];
            char c2 = text[i + 1];
            auto pos1 = findPosition(c1);
            auto pos2 = findPosition(c2);

            if (pos1.first == pos2.first)
            {
                result += matrix[pos1.first][(pos1.second + 1) % 5];
                result += matrix[pos2.first][(pos2.second + 1) % 5];
            }
            else if (pos1.second == pos2.second)
            {
                result += matrix[(pos1.first + 1) % 5][pos1.second];
                result += matrix[(pos2.first + 1) % 5][pos2.second];
            }
            else
            {
                result += matrix[pos1.first][pos2.second];
                result += matrix[pos2.first][pos1.second];
            }
        }
        return result;
    }

    void displayMatrix()
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    string decrypt(string text)
    {
        string result = "";
        for (int i = 0; i < text.length(); i += 2)
        {
            char c1 = text[i];
            char c2 = text[i + 1];
            auto pos1 = findPosition(c1);
            auto pos2 = findPosition(c2);
    
            if (pos1.first == pos2.first)
            {
                result += matrix[pos1.first][(pos1.second + 4) % 5];
                result += matrix[pos2.first][(pos2.second + 4) % 5];
            }
            else if (pos1.second == pos2.second)
            {
                result += matrix[(pos1.first + 4) % 5][pos1.second];
                result += matrix[(pos2.first + 4) % 5][pos2.second];
            }
            else
            {
                result += matrix[pos1.first][pos2.second];
                result += matrix[pos2.first][pos1.second];
            }
        }
        
        // Remove  added 'X' where necessary
        string finalResult = "";
        for (int  i = 0; i < result.length(); i++)
        {
            if (i > 0 && result[i] == 'X' && result[i - 1] == result[i + 1])
            {
                continue;
            }

            //if x at last 
            if (i == result.length() - 1 && result[i] == 'X')
            {
                continue;
            }
            finalResult += result[i];
        }
        
        return finalResult;
    }
    
};

int main()
{
    PlayfairCipher cipher("MONARCHY");
    cout << "Playfair Matrix" << endl;
    cipher.displayMatrix();

    string plaintext = "BALLOON";
    string ciphertext = cipher.encrypt(plaintext);
    string decrypttext = cipher.decrypt(ciphertext);
    cout << "\nPlaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "originla: " << decrypttext << endl;

    return 0;
}
# Playfair Cipher Implementation in C++

## Introduction
This project is a C++ implementation of the **Playfair Cipher**, a classical encryption technique that uses a **5x5 matrix** to encrypt and decrypt messages. This implementation ensures:
- Encryption and decryption of text using a **key matrix**.
- Handling of duplicate letters and the letter 'J'.
- Proper formatting of digraphs (pairs of letters) for encryption.

## Features
- Generates a **5x5 Playfair cipher matrix** based on a given key.
- Encrypts a given plaintext message.
- Decrypts the ciphertext back to its original message.
- Removes added padding (e.g., extra 'X' used in encryption).
- Displays the Playfair matrix used for encryption.

## How It Works
### 1. Matrix Generation
- A key is used to construct a 5x5 matrix.
- Duplicate letters in the key are removed.
- The letter **'J' is replaced with 'I'**.
- The rest of the alphabet (excluding 'J') is filled in the matrix.

### 2. Encryption Process
- The plaintext is **converted to uppercase**.
- The letter **'J' is replaced with 'I'**.
- The text is split into **digraphs (pairs of letters)**.
  - If a pair contains duplicate letters, an 'X' is inserted.
  - If the length is odd, an 'X' is appended.
- Based on the Playfair cipher rules, each digraph is transformed into ciphertext.

### 3. Decryption Process
- The ciphertext is processed in digraphs.
- The original text is restored using the **inverse Playfair rules**.
- Extra 'X' characters added during encryption are removed when appropriate.

## Compilation & Execution
### Compilation:
Use a **C++ compiler** (like g++) to compile the code:
```sh
 g++ playfair_cipher.cpp -o playfair_cipher
```
### Execution:
Run the compiled program:
```sh
 ./playfair_cipher
```

## Example Output
```
Playfair Matrix
M O N A R
C H Y B D
E F G I K
L P Q S T
U V W X Z

Plaintext: BALLOON
Ciphertext: ICMRRPNA
Original: BALLOON
```

## Code Structure
- **PlayfairCipher class**:
  - `createMatrix()`: Generates the Playfair matrix.
  - `encrypt()`: Encrypts a given text.
  - `decrypt()`: Decrypts the given ciphertext.
  - `findPosition()`: Finds the position of a character in the matrix.
  - `displayMatrix()`: Displays the Playfair matrix.

- **main() function**:
  - Creates an instance of the `PlayfairCipher` class with the key "MONARCHY".
  - Encrypts and decrypts a sample plaintext message.
  - Displays the results.

## Notes
- The program handles special cases where duplicate letters or missing letters might be an issue.
- The letter 'J' is always treated as 'I'.
- The program appends 'X' where necessary but removes it intelligently during decryption.

## License
This project is open-source and can be used freely for educational purposes.


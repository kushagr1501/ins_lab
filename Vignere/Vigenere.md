# Vigenère Cipher Implementation in C++

## Introduction
This project implements the **Vigenère Cipher**, a polyalphabetic substitution cipher that encrypts messages using a repeated keyword. This implementation ensures:
- Encryption and decryption of messages using a **repeating key**.
- Automatic handling of spaces and non-alphabetic characters.
- Conversion of messages and keys to uppercase for consistency.

## Features
- **Cleans input strings** to remove non-alphabetic characters.
- Encrypts a plaintext message using a repeating key.
- Decrypts the encrypted text back to the original message.

## How It Works
### 1. Cleaning the String
- Removes all non-alphabetic characters from the input.
- Converts all characters to **uppercase** for uniform processing.

### 2. Encryption Process
- Each letter in the plaintext is shifted forward based on the corresponding letter in the key.
- The key repeats cyclically to match the message length.
- Formula used:
  ```plaintext
  Encrypted[i] = (Message[i] + Key[i]) % 26
  ```

### 3. Decryption Process
- The encrypted text is reversed by shifting characters backward based on the key.
- The same repeated key is used for decryption.
- Formula used:
  ```plaintext
  Decrypted[i] = (Encrypted[i] - Key[i] + 26) % 26
  ```

## Compilation & Execution
### Compilation:
Use a **C++ compiler** (such as g++):
```sh
 g++ vigenere_cipher.cpp -o vigenere_cipher
```

### Execution:
Run the compiled program:
```sh
 ./vigenere_cipher
```

## Example Output
```
Encrypted message: RIJVSUYVJN
Decrypted message: HELLOWORLD
```

## Code Structure
- **cleanString()**: Removes non-alphabetic characters and converts the string to uppercase.
- **encrypt()**: Encrypts a given plaintext using the Vigenère cipher.
- **decrypt()**: Decrypts the given ciphertext back to plaintext.
- **main()**:
  - Encrypts a sample message using the key "KEY".
  - Decrypts the message back to its original form.
  - Displays both the encrypted and decrypted messages.

## Notes
- The implementation ignores spaces and punctuation while processing text.
- The key is **repeated cyclically** to match the message length.
- Negative shifts are handled using modular arithmetic (`+26`).

## License
This project is open-source and can be used freely for educational purposes.


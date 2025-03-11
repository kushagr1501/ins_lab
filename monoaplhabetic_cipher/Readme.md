# MonoAlphabetic Cipher Implementation in C++

## Introduction
This project implements the **Atbash Cipher**, a simple monoalphabetic substitution cipher where each letter in the alphabet is mapped to its reverse counterpart (e.g., A → Z, B → Y, etc.).

## Features
- Encrypts plaintext by replacing each letter with its reverse counterpart.
- Decrypts ciphertext by applying the same transformation.
- Ignores non-alphabetic characters (they remain unchanged).

## How It Works
### 1. Encryption Process
- Creates a **mapping** between each letter and its reverse counterpart.
- Reads a plaintext message and replaces each letter with its mapped counterpart.
- Keeps non-alphabetic characters unchanged.

### 2. Decryption Process
- The Atbash cipher is **self-inverting**, meaning the encryption and decryption processes are identical.
- Uses the reverse mapping to decrypt the text back to the original message.

## Compilation & Execution
### Compilation:
Use a **C++ compiler** (such as g++):
```sh
g++ atbash_cipher.cpp -o atbash_cipher
```

### Execution:
Run the compiled program:
```sh
./atbash_cipher
```

## Example Output
```
Enter the message:
HELLO
Encrypted text is: SVYYO
Decrypted text is: HELLO
```

## Code Structure
- **Mapping Setup**: Generates a map for encryption and decryption.
- **Encryption Function**: Iterates through plaintext and applies Atbash transformation.
- **Decryption Function**: Uses the same mapping to reverse the encryption.
- **main()**:
  - Prompts the user for input.
  - Encrypts the input using the Atbash cipher.
  - Decrypts the text back to the original form.
  - Displays the results.

## Notes
- The Atbash cipher is **symmetrical**, meaning encryption and decryption are the same operations.
- Works only with uppercase English letters (spaces and symbols remain unchanged).
- This cipher is **not secure** for modern cryptographic applications but serves as a simple educational example.

## License
This project is open-source and can be used freely for educational purposes.


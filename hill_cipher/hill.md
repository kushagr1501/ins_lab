# Hill Cipher Implementation in C++

## Introduction
This project implements the **Hill Cipher**, a polygraphic substitution cipher based on matrix multiplication in **modulo 26 arithmetic**. The implementation includes:
- Matrix-based encryption using a key matrix.
- Matrix-based decryption using the inverse of the key matrix.
- Handling of uppercase characters and padding.

## Features
- Encrypts plaintext using a **2x2 matrix key**.
- Decrypts ciphertext using the **inverse of the key matrix**.
- Handles uppercase conversion and padding with 'X'.
- Computes the determinant and modular inverse for decryption.

## How It Works
### 1. Encryption Process
- Converts plaintext to uppercase.
- Ensures the length of plaintext is a multiple of the matrix size (by adding 'X' padding if needed).
- Converts plaintext letters into numerical values (A=0, B=1, ..., Z=25).
- Performs **matrix multiplication** between the key matrix and plaintext blocks.
- Applies **mod 26** to get encrypted values.
- Converts numerical values back to letters to form the ciphertext.

### 2. Decryption Process
- Computes the **determinant** of the key matrix.
- Finds the **modular inverse** of the determinant.
- Calculates the **adjugate (adjoint) matrix** of the key matrix.
- Multiplies the adjugate matrix by the modular inverse to get the **inverse key matrix**.
- Decrypts ciphertext by multiplying the inverse key matrix with ciphertext blocks.
- Applies **mod 26** to recover original values and convert them back to letters.

## Compilation & Execution
### Compilation:
Use a **C++ compiler** (such as g++):
```sh
g++ hill_cipher.cpp -o hill_cipher
```

### Execution:
Run the compiled program:
```sh
./hill_cipher
```

## Example Output
```
Encrypted text: ZEBBXC
Decrypted text: HELLOX
```

## Code Structure
- **multi()**: Multiplies a matrix with a block of numbers and applies **mod 26**.
- **fn()**: Encrypts the plaintext by applying the Hill Cipher algorithm.
- **determinant()**: Computes the determinant of a **2x2** matrix.
- **modInverse()**: Finds the modular inverse of the determinant.
- **adjoint()**: Computes the adjugate (adjoint) of the key matrix.
- **decrypt()**: Uses the inverse of the key matrix to decrypt ciphertext.
- **main()**:
  - Encrypts the message "HELLO" using the key matrix `{{6, 24}, {1, 13}}`.
  - Decrypts the message back to its original form.
  - Displays both encrypted and decrypted messages.

## Notes
- The key matrix must be **invertible (determinant must have a modular inverse in mod 26)**.
- The plaintext is padded with 'X' if necessary to match matrix size requirements.
- Negative values are handled correctly using modular arithmetic (`+26`).

## License
This project is open-source and can be used freely for educational purposes.


# RSA Encryption and Decryption in C++

## Description
This project demonstrates the implementation of RSA encryption and decryption using basic C++.

## How It Works
1. The user inputs two prime numbers (`p` and `q`).
2. The program computes:
   - `n = p * q`
   - `phi = (p - 1) * (q - 1)`
3. A public exponent `e` is selected such that `gcd(e, phi) = 1`.
4. The private key `d` is calculated as the modular inverse of `e` modulo `phi`.
5. A message is encrypted using `c = (msg^e) % n`.
6. The encrypted message is decrypted using `decrypted = (c^d) % n`.

## Prerequisites
- A C++ compiler (e.g., `g++` for Linux/macOS, or MinGW for Windows).

## Steps to Run the Program
1. Save the RSA implementation code in a file (e.g., `rsa.cpp`).
2. Open a terminal or command prompt and navigate to the file’s directory.
3. Compile the program using:
   ```sh
   g++ rsa.cpp -o rsa
   ```
4. Run the program:
   ```sh
   ./rsa   # On Linux/macOS
   rsa.exe # On Windows
   ```
5. Enter the values for `p`, `q`, and `msg` when prompted.
6. The program will display the encrypted and decrypted message.

## Example Output
```
Enter the value of p:
7
Enter the value of q:
17
Enter a message:
12
Encrypted message: 57
Decrypted message: 12
```

## Notes
- Ensure that `p` and `q` are prime numbers.
- The message `msg` should be less than `n`.
- The encryption and decryption use modular exponentiation.

## License
This project is open-source and free to use.


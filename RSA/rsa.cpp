
#include<bits/stdc++.h>
using namespace std;
int gcd(int a, int b) {
while (b != 0) {
int temp = b;
b = a % b;
a = temp;
}
return a;
}
void RSA(int p, int q, int msg) {
int n = p * q;
int phi = (p - 1) * (q - 1);
int e = 0;
for (int i = 2; i < phi; i++) {
if (gcd(i, phi) == 1) {
e = i;
break;
}
}
int d = 0;
for (int j = 1; j < phi; j++) {
if ((j * e) % phi == 1) {
d = j;
break;
}
}
int c = 1;
for (int i = 0; i < e; i++) {
c = (c * msg) % n;
}
cout << "Encrypted message: " << c << endl;
int decrypted = 1;
for (int i = 0; i < d; i++) {
decrypted = (decrypted * c) % n;
}
cout << "Decrypted message: " << decrypted << endl;
}
int main() {
int p, q, msg;
cout << "Enter the value of p: "<<endl;
cin >> p;
cout << "Enter the value of q: ";
cin >> q;
cout << "Enter a message: ";
cin >> msg;
RSA(p, q, msg);
return 0;
}
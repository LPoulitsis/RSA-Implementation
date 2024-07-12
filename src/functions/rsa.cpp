#include "../headers/rsa.hh"

#include <cmath>
#include <iostream>
#include <random>
#include <sstream>

using namespace std;

// A small set of prime numbers
int primeNumbers[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                      43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

int p, q;

Rsa::Rsa() { KeyGeneration(); }

PublicKey Rsa::GetPublicKey() const { return *publicKey; }

PrivateKey Rsa::GetPrivateKey() const { return *privateKey; }

int Rsa::Phi(int N) { return (p - 1) * (q - 1); }

void Rsa::TwoRandomPrimeNumbers() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 25);

    // Generate the random prime number for p
    p = primeNumbers[dis(gen)];

    // Generate the random prime number for q
    q = primeNumbers[dis(gen)];

    // Ensure p and q are distinct
    while (q == p) {
        q = primeNumbers[dis(gen)];
    }
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;

    // Apply Extended Euclidean Algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algorithm
        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0) x1 += m0;

    return x1;
}

void Rsa::TwoRandomIntegers(int& e, int& d) {
    int phi = Phi(GetPublicKey().GetN());

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(2, phi - 1);

    do {
        e = dis(gen);
    } while (gcd(e, phi) != 1);

    d = modInverse(e, phi);
}

void Rsa::KeyGeneration() {
    // Step (1)
    TwoRandomPrimeNumbers();  // Get p, q prime numbers
    int N = p * q;            // Calculate their product

    publicKey = new PublicKey();
    privateKey = new PrivateKey();

    publicKey->SetN(N);
    privateKey->SetN(N);

    // Step (2)
    int e, d;
    TwoRandomIntegers(e, d);  // Choose two random integers for e, d
    publicKey->SetE(e);
    privateKey->SetD(d);
}

int modExp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

string Rsa::RsaEncrypt(string message) {
    const char* c_message = message.c_str();
    string ciphertext = "";
    int N = GetPublicKey().GetN();
    int e = GetPublicKey().GetE();

    for (size_t i = 0; i < message.size(); i++) {
        int charValue = static_cast<int>(c_message[i]);
        int y = modExp(charValue, e, N);  // y = (x ^ e) mod N
        ciphertext += to_string(y) + " ";
    }
    return ciphertext;
}

string Rsa::RsaDecrypt(string ciphertext) {
    string plaintext = "";
    int N = GetPrivateKey().GetN();
    int d = GetPrivateKey().GetD();
    int x;
    stringstream ss(ciphertext);
    string temp;
    while (ss >> temp) {
        x = stoi(temp);
        x = modExp(x, d, N);  // x = (y ^ d) mod N
        plaintext += static_cast<char>(x);
    }
    return plaintext;
}

// PublicKey Class Implementations
void PublicKey::SetE(int e) { PublicKey::e = e; }
void PublicKey::SetN(int N) { PublicKey::N = N; }

int PublicKey::GetE() { return e; }
int PublicKey::GetN() { return N; }

// PrivateKey Class Implementations
void PrivateKey::SetD(int d) { PrivateKey::d = d; }
void PrivateKey::SetN(int N) { PrivateKey::N = N; }

int PrivateKey::GetD() { return d; }
int PrivateKey::GetN() { return N; }

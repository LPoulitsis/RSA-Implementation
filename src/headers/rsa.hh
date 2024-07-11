#pragma once

#include <cmath>
#include <iostream>
#include <random>
#include <string>

using namespace std;
class PublicKey {
   public:
    void SetE(int e);
    void SetN(int N);

    int GetE();
    int GetN();

   private:
    // Public key consists of (N, e)
    int N;
    int e;
};

class PrivateKey {
   public:
    void SetD(int d);
    void SetN(int N);

    int GetD();
    int GetN();

   private:
    // Private key consists of (N, d)
    int N;
    int d;
};

class Rsa {
   public:
    // Constructor that will call the KeyGeneration method
    Rsa();

    // Deconstructor that deletes this object instance
    ~Rsa();

    string RsaEncrypt(string message);

    string RsaDecrypt(string ciphertext);

    PublicKey GetPublicKey() const;

    PrivateKey GetPrivateKey() const;

   private:
    PublicKey publicKey;
    PrivateKey privateKey;

    // Generates the public and private keys needed for the user
    void KeyGeneration();

    // Generates two random prime numbers p, q
    void TwoRandomPrimeNumbers();

    // Generates two random integers e, d
    void TwoRandomIntegers(int& e, int& d);

    // Calculates Φ(Ν) = N - p - q + 1 and returns the outcome
    int Phi(int N);
};
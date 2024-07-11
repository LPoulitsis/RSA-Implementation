#include <iostream>

using namespace std;

class RsaProperties {
   public:
    // Generates the public and private keys needed for the user
    void KeyGeneration();

    string RsaEncrypt(string message);

    string RsaDecrypt(string ciphertext);

    PublicKey GetPublicKey();

    PrivateKey GetPrivateKey();

   private:
    PublicKey publicKey;
    PrivateKey privateKey;

    // Constructor that will call the KeyGeneration method
    RsaProperties();

    // Generates two random prime numbers p, q
    void TwoRandomPrimeNumbers(int& p, int& q);

    // Generates two random integers e, d
    void TwoRandomIntegers(int& e, int& d);

    // Calculates Φ(Ν) = N - p - q + 1 and returns the outcome
    int Phi(int N);
};

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
    void SetE(int e);
    void SetN(int N);

    int GetE();
    int GetN();

   private:
    // Private key consists of (N, d)
    int N;
    int d;
};
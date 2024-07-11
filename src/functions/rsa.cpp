#include "../headers/rsa.hh"

// A small set of prime numbers
int primeNumbers[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                      43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

int p, q;

Rsa::Rsa() { KeyGeneration(); }

PublicKey Rsa::GetPublicKey() const { return *publicKey; }

PrivateKey Rsa::GetPrivateKey() const { return *privateKey; }

int Rsa::Phi(int N) { return N - p - q + 1; }

void Rsa::TwoRandomPrimeNumbers() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 25);

    // Generate the random prime number for p
    p = primeNumbers[dis(gen)];

    // Generate the random prime number for q
    q = primeNumbers[dis(gen)];
}

void Rsa::TwoRandomIntegers(int& e, int& d) {
    // We have to conform with the rule e * d = 1 mod Φ(Ν)
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    do {
        e = dis(gen);
        d = dis(gen);
    } while ((e * d) != (1 % Phi(GetPublicKey().GetN())));
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

string Rsa::RsaEncrypt(string message) {
    const char* c_message = message.c_str();
    string ciphertext = "";
    int N = GetPublicKey().GetN();
    int e = GetPublicKey().GetE();
    int y;
    for (size_t i = 0; i < message.size(); i++) {
        int charValue = static_cast<int>(c_message[i]);
        y = (int)pow(charValue, e) % N;  // y = (x ^ e) mod N
        ciphertext += to_string(y) + " ";
    }
    return ciphertext;
}

string Rsa::RsaDecrypt(string ciphertext) {
    string message = "";
    int N = GetPrivateKey().GetN();
    int d = GetPrivateKey().GetD();
    int x;

    // convert ciphertext to message string
    stringstream ss(ciphertext);
    string token;
    while (getline(ss, token, ' ')) {
        x = stoi(token);
        int y = (int)pow(x, d) % N;  // y = (x ^ d) mod N
        message += static_cast<char>(y);
    }

    return message;
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

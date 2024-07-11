#include "headers/user.hh"

int main() {
    User* bob = new User("Bob");
    User* alice = new User("Alice");

    bob->SendMessageTo();
    string ciphertext = bob->GetProperties().RsaEncrypt(bob->GetMessage());
    cout << bob->GetName() << " sent to " << alice->GetName() << " with id "
         << alice->GetID() << " this message: " << ciphertext << endl;

    alice->GetMessageFrom(ciphertext, 2);
    string text = alice->GetProperties().RsaDecrypt(ciphertext);

    cout << alice->GetName() << " received from " << bob->GetName()
         << " with id " << bob->GetID() << " this message: " << text << endl;

    return 0;
}
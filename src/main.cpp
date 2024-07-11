#include "headers/user.hh"

int main() {
    User* bob = new User("Bob");
    User* alice = new User("Alice");

    bob->SendMessageTo();
    cout << bob->GetMessage();
    string ciphertext = bob->GetProperties().RsaEncrypt(bob->GetMessage());

    cout << bob->GetName() << " sent to " << alice->GetName() << " with id "
         << alice->GetID() << " this message: " << ciphertext;

    alice->GetMessageFrom(ciphertext, 2);
    string text = alice->GetProperties().RsaDecrypt(ciphertext);

    cout << alice->GetName() << " received from " << bob->GetName()
         << " with id " << bob->GetID() << " this message: " << text;

    return 0;
}
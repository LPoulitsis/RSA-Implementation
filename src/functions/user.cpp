#include "../headers/user.hh"

User::User(string name) {
    User::name = name;
    IncrementID();
}

int User::GetID() { return id; }

string User::GetName() { return name; }

Rsa User::GetProperties() { return properties; }

void User::SendMessageTo() {
    cout << "Type an id to send the message to: ";
    cin >> id;
    cout << "Type the message to send: ";
    cin >> message;
}

void User::GetMessageFrom(string message, int id) {
    if (User::id == id) {
        User::message = message;
    }
}

void User::IncrementID() { id++; }
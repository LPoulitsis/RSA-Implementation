#include "rsa.hh"

class User {
   public:
    User(string name);
    int GetID();
    string GetName();
    Rsa GetProperties();
    void SendMessageTo();
    void GetMessageFrom(string message, int id);

   private:
    Rsa properties;
    string name;
    int id;
    string message;
    void IncrementID();
};
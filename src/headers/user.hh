#include "rsa.hh"

class User {
   public:
    User(string name);
    int GetID();
    string GetName();
    Rsa GetProperties();
    string SendMessageTo(int id);
    string GetMessageFrom(int id);

   private:
    Rsa properties;
    int id;
    void IncrementID();
};
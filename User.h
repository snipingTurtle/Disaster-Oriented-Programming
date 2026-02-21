#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User{
private:
    int id;
    string name;
    string priviledges;

public:
    // constructors
    User();
    User(const int &user_id, const string &s, const string &priv);

    // member functions
    void Register();
    void LogIn();
    void LogOut();

    // destructor
    ~User();
};

#endif
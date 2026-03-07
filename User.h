#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User
{
private:
    int id;
    string name;
    string priviledges;

public:
    // constructors
    User();
    User(const int &user_id, const string &s, const string &priv);

    // getters
    int getId() const;
    string getName() const;
    string getPriviledges() const;

    // member functions
    void Register();
    void LogIn();
    void LogOut();

    // destructor
    virtual ~User(); // making it virtual to ensure proper derived class cleanup
};

#endif
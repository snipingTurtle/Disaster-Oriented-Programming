#ifndef USER_HPP
#define USER_HPP

#include <string>

using namespace std;

class User {
private:
    int id;
    string name;
    string priviledges;

public:
    User() : id(0), name("NULL"), priviledges("NULL") {}

    User(const int& user_id, const string& s, const string& priv)
        : id(user_id), name(s), priviledges(priv) {}

    int getId() const;
    string getName() const;
    string getPriviledges() const;

    void Register();
    void LogIn();
    void LogOut();

    virtual ~User();
};

#endif
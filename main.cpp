#include <iostream>

using namespace std;

class User
{
private:
    int id;
    string name;
    string priviledges;

public:
    User() : id(0), name("NULL"), priviledges("NULL")
    {
    }

    User(const int &user_id, const string &s, const string &priv) : id(user_id), name(s), priviledges(priv)
    {
    }

    void Register()
    {

    }

    void LogIn()
    {

    }

    void LogOut()
    {
        
    }

    ~User()
    {
    }
};

int main()
{
}
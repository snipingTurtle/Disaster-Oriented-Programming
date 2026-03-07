#include "User.h"

// default constructor
User::User() : id(0), name("NULL"), priviledges("NULL")
{
}

// parameterized constructor
User::User(const int &user_id, const string &s, const string &priv)
    : id(user_id), name(s), priviledges(priv)
{
}

// getters
int User::getId() const
{
    return id;
}

string User::getName() const
{
    return name;
}

string User::getPriviledges() const
{
    return priviledges;
}

// Member functions
void User::Register()
{
}

void User::LogIn()
{
}

void User::LogOut()
{
}

// Destructor
User::~User()
{
}
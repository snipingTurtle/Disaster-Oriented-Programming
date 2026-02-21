#include "User.h"

// Default constructor
User::User() : id(0), name("NULL"), priviledges("NULL")
{
}

// parameterized constructor
User::User(const int &user_id, const string &s, const string &priv) : id(user_id), name(s), priviledges(priv)
{
}

// member functions
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
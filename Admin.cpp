#include "Admin.h"

// constructor
Admin::Admin(int id,
             const string &name,
             const string &privileges,
             const string &post,
             int accessLevel) : User(id, name, privileges), post(post), accessLevel(accessLevel){}

// getter functions
string Admin::getPost() const
{
    return post;
}

string Admin::getPhoneNumber() const
{
    return phoneNumber;
}

int Admin::getAccessLevel() const
{
    return accessLevel;
}


// setter functions
void Admin::setPhoneNumber(const string &phone)
{
    phoneNumber = phone;
}

void Admin::setAccessLevel(int level)
{
    accessLevel = level;
}


void Admin::postNotice(const string &text)
{
    cout<< "[" <<post<< "] Notice: "<<text<<endl;
}


// destructor
Admin::~Admin(){}
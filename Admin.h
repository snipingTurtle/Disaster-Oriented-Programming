#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>
#include <iostream>
using namespace std;

class Admin : public User
{
protected:
    string post;
    string phoneNumber;
    int accessLevel;

public:
    // CONSTRUCTOR
    Admin(int id,
          const string &name,
          const string &privileges,
          const string &post,
          int accessLevel); // No phone number as im keeping it optional, not core info

    
    // GETTER FUNCTIONS
    string getPost() const;
    string getPhoneNumber() const;
    int getAccessLevel() const;


    // SETTER FUNCTIONS
    void setPhoneNumber(const string &phone);
    void setAccessLevel(int level);


    virtual void postNotice(const string &text);


    // PURE VIRTUAL FUNCTIONS
    virtual void updateComplaintStatus(int complaintId, const string &status) = 0;
    virtual void viewResidents() const = 0;
    virtual string role() const = 0;


    // DESTRUCTOR
    virtual ~Admin();
};

#endif
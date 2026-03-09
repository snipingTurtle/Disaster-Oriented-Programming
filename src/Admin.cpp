#include "Admin.h"
#include "notice_board.hpp"

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

string Admin::getEmail() const
{
    return email;
}

string Admin::getOfficeRoom() const
{
    return officeRoom;
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

void Admin::setEmail(const string &email)
{
    this->email = email;
}

void Admin::setOfficeRoom(const string &room)
{
    officeRoom = room;
}

void Admin::postNotice(NoticeBoard &notice,
                       const string &title,
                       const string &announcement,
                       const string &timestamp)
{
    notice.SetTitle(title);
    notice.SetAuthor(getName());
    notice.SetTimestamp(timestamp);
    notice.SetAnnouncement(announcement);

    cout<<"[" << role() << "] posted notice successfully." << endl;
}

void Admin::viewProfile() const
{
    cout << "\n----- Admin Profile -----\n";
    cout << "Name: " << getName() << endl;
    cout << "Role: " << role() << endl;
    cout << "Post: " << post << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Email: " << email << endl;
    cout << "Office Room: " << officeRoom << endl;
    cout << "Access Level: " << accessLevel << endl;
    cout << "Privileges: " << getPriviledges() << endl;
    cout << "-------------------------\n";
}


// destructor
Admin::~Admin(){}
#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "user.hpp"
#include <iostream>
#include <string>

using namespace std;

class Complaint;
class NoticeBoard;

class Admin : public User {
protected:
    string post;
    string phoneNumber;
    int accessLevel;
    string email;
    string officeRoom;

public:
    Admin(int id, const string& name, const string& privileges,const string& post, int accessLevel);

    string getPost() const;
    string getPhoneNumber() const;
    int getAccessLevel() const;
    string getEmail() const;
    string getOfficeRoom() const;

    void setPhoneNumber(const string& phone);
    void setAccessLevel(int level);
    void setEmail(const string& email);
    void setOfficeRoom(const string& room);

    virtual void postNotice(NoticeBoard& notice,
                            const string& title,
                            const string& announcement,
                            const string& timestamp);

    virtual void viewProfile() const;

    virtual void updateComplaintStatus(Complaint& complaint,
                                       const string& status) = 0;
    virtual void viewResidents() const = 0;
    virtual string role() const = 0;

    virtual ~Admin();
};

#endif
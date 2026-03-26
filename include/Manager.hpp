#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Admin.hpp"
#include "complaint.hpp"

class Manager : public Admin {
public:
    Manager();
    Manager(int id, const string& name, const string& privileges, const string& post, int accessLevel);

    void updateNotice(int id, const string& title, const string& text) override;
    void updateComplaintStatus(Complaint& complaint, const string& status) override;
    void viewResidents() const override;
    string role() const override;

    ~Manager();
};

#endif

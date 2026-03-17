#ifndef ASSISTANT_PROVOST_HPP
#define ASSISTANT_PROVOST_HPP

#include "Admin.hpp"
#include <string>

using namespace std;

class Complaint;

class AssistantProvost : public Admin {
protected:
    string responsibility;
public:
    AssistantProvost(int id, const string& name, const string& responsibility);

    string getResponsibility() const;

    void updateComplaintStatus(Complaint& complaint, const string& status) override;

    void viewResidents() const override;
    virtual string role() const = 0;

    virtual ~AssistantProvost();
};

#endif
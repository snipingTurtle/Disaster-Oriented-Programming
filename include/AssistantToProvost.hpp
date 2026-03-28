#ifndef ASSISTANT_TO_PROVOST_HPP
#define ASSISTANT_TO_PROVOST_HPP

#include "Admin.hpp"
#include <string>
using namespace std;

class Provost;
class Complaint;

class AssistantToProvost : public Admin {
    friend class Provost;

protected:
    string responsibility;
    string shift;

private:
    void setShift(const string& shift);

public:
    AssistantToProvost(int id,
                       const string& name,
                       const string& responsibility,
                       const string& shift);

    string getResponsibility() const;
    string getShift() const;

    void updateComplaintStatus(Complaint& complaint, const string& status) override;

    void viewResidents() const override;

    string role() const override = 0;

    virtual ~AssistantToProvost();
};

#endif
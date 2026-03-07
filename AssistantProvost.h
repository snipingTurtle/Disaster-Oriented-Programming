#ifndef ASSISTANT_PROVOST_H
#define ASSISTANT_PROVOST_H

#include <string>
#include "Admin.h"

using namespace std;


class AssistantProvost : public Admin{
protected:
    string responsibility;

public:
    AssistantProvost(int id,
                     const string &name,
                     const string &responsibility);

    void updateComplaintStatus(int complaintId,const string &status) override;
    void viewResidents() const override;

    // keeps this class abstract
    virtual string role() const = 0;
    virtual ~AssistantProvost();
};


#endif
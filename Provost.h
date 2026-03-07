#ifndef PROVOST_H
#define PROVOST_H

using namespace std;

#include "Admin.h"


class Provost : public Admin{
private:
    static int provostCount;
public:
    Provost(int id, const string &name);

    void updateComplaintStatus(int complaintId, const string &status) override;
    void viewResidents() const override;
    string role() const override;

    ~Provost();
};

#endif
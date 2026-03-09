#ifndef PROVOST_H
#define PROVOST_H

using namespace std;

#include "Admin.h"

class AssistantToProvost;

class Provost : public Admin{
private:
    static int provostCount;
    const int appointmentYear;
public:
    Provost(int id, const string &name, int appointmentYear);

    int getAppointmentYear() const;
    void assignShift(AssistantToProvost &assistant, const string &shift);

    void updateComplaintStatus(int complaintId, const string &category, const string &status) override;
    void viewResidents() const override;
    string role() const override;

    ~Provost();
};

#endif
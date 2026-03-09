#ifndef PROVOST_H
#define PROVOST_H

using namespace std;

#include "Admin.hpp"

class AssistantToProvost;
class Complaint;

class Provost : public Admin{
private:
    static int provostCount;
    const int appointmentYear;
public:
    Provost(int id, const string &name, int appointmentYear);

    int getAppointmentYear() const;
    void assignShift(AssistantToProvost &assistant, const string &shift);

    void updateComplaintStatus(Complaint &complaint,const string &status) override;
    void viewResidents() const override;
    string role() const override;

    ~Provost();
};

#endif
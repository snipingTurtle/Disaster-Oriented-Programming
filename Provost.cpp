#include "Provost.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int Provost::provostCount = 0;

Provost::Provost(int id,const string &name)
    : Admin(id, name, "Admin", "Provost",10)
{
    if(provostCount >= 1)
    {
        throw runtime_error("Only ONE Provost is allowed in the system.");
    }
    provostCount++;
}

void Provost::updateComplaintStatus(int complaintId, const string &status)
{
    cout<<"Provost updated complaint "<<complaintId << " to status: "<<status<< endl;
}

void Provost::viewResidents() const // Not implemented yet
{
    cout<< "Provost is viewing all residents."<<endl;
}

string Provost::role() const
{
    return "Provost";
}

Provost::~Provost()
{
    provostCount--;
}
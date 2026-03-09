#include "Provost.h"
#include <iostream>
#include <stdexcept>
#include "AssistantToProvost.h"
#include "complaint.hpp"
#include "database_handler.hpp"

using namespace std;

int Provost::provostCount = 0;

Provost::Provost(int id,const string &name, int appointmentYear)
    : Admin(id, name, "Admin", "Provost",10), appointmentYear(appointmentYear)
{
    if(provostCount >= 1)
    {
        throw runtime_error("Only ONE Provost is allowed in the system.");
    }
    provostCount++;
}

int Provost::getAppointmentYear() const
{
    return appointmentYear;
}

void Provost::assignShift(AssistantToProvost &assistant, const string &shift)
{
    assistant.setShift(shift);

    cout<<"Provost assigned shift '"<<shift<<"' to "<< assistant.role() << endl;
}


void Provost::updateComplaintStatus(Complaint &complaint, const string &status)
{
    complaint.UpdateStatus(status);
    DatabaseHandler::UpdateComplaintStatus(complaint.GetComplaintID(), status);

    cout << "Provost updated complaint ID "<< complaint.GetComplaintID()<< " to status: " << status << endl;
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
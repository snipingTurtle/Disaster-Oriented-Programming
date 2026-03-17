#include "AssistantToProvost.hpp"
#include "complaint.hpp"
#include "database_handler.hpp"

#include <iostream>

using namespace std;

AssistantToProvost::AssistantToProvost(int id,
                                       const string& name,
                                       const string& responsibility,
                                       const string& shift)
    : Admin(id, name, "Admin", "Assistant To Provost", 5),responsibility(responsibility),shift(shift) {
}

string AssistantToProvost::getResponsibility() const
{
    return responsibility;
}

string AssistantToProvost::getShift() const
{
    return shift;
}

void AssistantToProvost::setShift(const string& shift) {
    this->shift = shift;
}

void AssistantToProvost::updateComplaintStatus(Complaint& complaint, const string& status) {
    complaint.UpdateStatus(status);
    DatabaseHandler::UpdateComplaintStatus(complaint.GetComplaintID(), status);

    cout << "Assistant To Provost (" << responsibility << ") updated complaint ID "<< complaint.GetComplaintID()<< " to status: "<<status<<endl;
}

void AssistantToProvost::viewResidents() const {
    cout << "Assistant To Provost responsible for "<<responsibility<<" is viewing relevant residents." << endl;
}

AssistantToProvost::~AssistantToProvost() 
{}
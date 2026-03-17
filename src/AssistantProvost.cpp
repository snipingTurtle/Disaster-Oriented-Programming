#include "AssistantProvost.hpp"
#include "complaint.hpp"
#include "database_handler.hpp"
#include <iostream>

using namespace std;

AssistantProvost::AssistantProvost(int id,
                                   const string& name,
                                   const string& responsibility)
    : Admin(id, name, "Admin", "Assistant Provost", 7), responsibility(responsibility) {
}

string AssistantProvost::getResponsibility() const {
    return responsibility;
}

void AssistantProvost::updateComplaintStatus(Complaint& complaint, const string& status) {
    complaint.UpdateStatus(status);
    DatabaseHandler::UpdateComplaintStatus(complaint.GetComplaintID(), status);

    cout << "Assistant Provost (" << responsibility<< ") updated complaint ID "<< complaint.GetComplaintID()<< " to status: " << status << endl;
}

void AssistantProvost::viewResidents() const {
    cout << "Assistant Provost responsible for "<< responsibility << " is viewing relevant residents." << endl;
}

AssistantProvost::~AssistantProvost() {}
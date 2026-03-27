#include "admin_complaint.hpp"
#include "database_handler.hpp"
#include <iostream>

using namespace std;

AdminComplaint::AdminComplaint() : Complaint() {}

AdminComplaint::AdminComplaint(int id, const string& text, int sID, const string& dateFiled)
    : Complaint(id, text, sID, dateFiled) {}

void AdminComplaint::UpdateStatus(const string& newStatus) {
    if (newStatus.empty()) {
        cout << "Error: Status cannot be empty!" << endl;
        return;
    }
    SetStatus(newStatus);  // uses base class setter
    DatabaseHandler::UpdateComplaintStatus(GetComplaintID(), newStatus);
    cout << "Success: Complaint status updated to " << newStatus << "." << endl;
}

void AdminComplaint::DeleteComplaint() {
    DatabaseHandler::DeleteComplaint(GetComplaintID());
    cout << "Success: Complaint #" << GetComplaintID() << " has been deleted." << endl;
}

AdminComplaint::~AdminComplaint() {}
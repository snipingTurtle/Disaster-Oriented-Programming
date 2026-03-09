#include "complaint.hpp"
#include "database_handler.hpp"
#include <iostream>

using namespace std;

Complaint::Complaint() : complaintID(0), complaintText(""), studentID(0), date(""), status("Pending") {}

Complaint::Complaint(int id, const string& text, int sID, const string& dateFiled) 
    : complaintID(id), complaintText(text), studentID(sID), date(dateFiled), status("Pending") {}

int Complaint::GetComplaintID() const {
    return complaintID;
}

string Complaint::GetComplaintText() const {
    return complaintText;
}

int Complaint::GetStudentID() const {
    return studentID;
}

string Complaint::GetDate() const {
    return date;
}

string Complaint::GetStatus() const {
    return status;
}

void Complaint::SetComplaint(const string& text) {
    if (text.empty()) {
        cout << "Error: Complaint text cannot be left empty!" << endl;
        return;
    }
    complaintText = text;
    DatabaseHandler::SaveComplaint(*this);
    cout << "Success: Complaint has been securely filed and logged in the database." << endl;
}

void Complaint::UpdateComplaint(const string& newText) {
    if (newText.empty()) {
        cout << "Error: Updated text cannot be empty!" << endl;
        return;
    }
    complaintText = newText;
    cout << "Success: Complaint details have been updated." << endl;
}

void Complaint::SetStatus(const string& s) {
    status = s;
}

void Complaint::UpdateStatus(const string& newStatus) {
    if (newStatus.empty()) {
        cout << "Error: Status cannot be empty!" << endl;
        return;
    }
    status = newStatus;
    cout << "Success: Complaint status updated to " << status << "." << endl;
}

void Complaint::DisplayComplaint() const {
    cout << "\n============================================\n";
    cout << "              COMPLAINT REPORT              \n";
    cout << "============================================\n";
    cout << "  Complaint ID : " << complaintID << "\n";
    cout << "  Student ID   : " << studentID << "\n";
    cout << "  Date Filed   : " << date << "\n";
    cout << "  Status       : " << status << "\n";
    cout << "--------------------------------------------\n";
    cout << "  Description  :\n  " << complaintText << "\n";
    cout << "============================================\n";
}

Complaint::~Complaint() {}

#include "complaint.hpp"
#include <iostream>

using namespace std;

Complaint::Complaint() : complaintID(0), complaintText(""), studentID(0), date("") {}

Complaint::Complaint(int id, const string& text, int sID, const string& dateFiled) 
    : complaintID(id), complaintText(text), studentID(sID), date(dateFiled) {}

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

void Complaint::SetComplaint(const string& text) {
    if (text.empty()) {
        cout << "Error: Complaint text cannot be left empty!" << endl;
        return;
    }
    complaintText = text;
    cout << "Success: Complaint has been securely filed." << endl;
}

void Complaint::UpdateComplaint(const string& newText) {
    if (newText.empty()) {
        cout << "Error: Updated text cannot be empty!" << endl;
        return;
    }
    complaintText = newText;
    cout << "Success: Complaint details have been updated." << endl;
}

void Complaint::UpdateStatus(const string& newStatus) {
}

Complaint::~Complaint() {}

#include "complaint.hpp"

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
}

void Complaint::UpdateComplaint(const string& newText) {
}

void Complaint::UpdateStatus(const string& newStatus) {
}

Complaint::~Complaint() {}

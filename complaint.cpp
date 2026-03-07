#include "complaint.hpp"

using namespace std;

Complaint::Complaint() : complaintID(0), complaintText(""), status("Pending") {}

Complaint::Complaint(int id, const string& text) : complaintID(id), complaintText(text), status("Pending") {}

int Complaint::GetComplaintID() const {
    return complaintID;
}

string Complaint::GetComplaintText() const {
    return complaintText;
}

string Complaint::GetStatus() const {
    return status;
}

void Complaint::SetComplaintID(int id) {
    complaintID = id;
}

void Complaint::SetComplaintText(const string& text) {
    complaintText = text;
}

void Complaint::SetStatus(const string& newStatus) {
    status = newStatus;
}

Complaint::~Complaint() {}

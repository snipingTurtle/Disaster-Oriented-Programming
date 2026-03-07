#include "complaint.hpp"

using namespace std;

Complaint::Complaint() : complaintID(0), complaintText("") {}

Complaint::Complaint(int id, const string& text) : complaintID(id), complaintText(text) {}

void Complaint::SetComplaint(const string& text) {
}

void Complaint::UpdateComplaint(const string& newText) {
}

void Complaint::UpdateStatus(const string& newStatus) {
}

Complaint::~Complaint() {}

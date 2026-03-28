#include "complaint.hpp"
#include "database_handler.hpp"
#include <iostream>

using namespace std;

int Complaint::nextID = 0;

Complaint::Complaint() : complaintID(nextID++), complaintText(""), studentID(0), date(""), status("Pending") {}

Complaint::Complaint(int id, const string& text, int sID, const string& dateFiled) 
    : complaintID(id), complaintText(text), studentID(sID), date(dateFiled), status("Pending") {
    if (id >= nextID) {
        nextID = id + 1;
    }
}

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
    DatabaseHandler::UpdateComplaintStatus(complaintID, status);
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

// Student-facing complaint panel — requires the student's ID to scope their complaints
void Complaint::run(int sID) {
    while (true) {
        cout << "\nComplaint Panel\n";
        cout << "1: View My Complaints\n";
        cout << "2: File a Complaint\n";
        cout << "3: Back\n";
        cout << "Choice: ";

        int c;
        cin >> c;
        cin.ignore();

        if (c == 3) break;

        else if (c == 1) {
            vector<Complaint> all = DatabaseHandler::LoadComplaints();
            bool found = false;
            for (auto& comp : all) {
                if (comp.GetStudentID() == sID) {
                    comp.DisplayComplaint();
                    found = true;
                }
            }
            if (!found) cout << "You have no complaints on record.\n";
        }

        else if (c == 2) {
            // Generate next ID
            vector<Complaint> all = DatabaseHandler::LoadComplaints();
            int newID = all.empty() ? 1 : all.back().GetComplaintID() + 1;

            string text, date;
            cout << "Enter complaint text: "; getline(cin, text);
            cout << "Enter date (YYYY-MM-DD): "; getline(cin, date);

            Complaint comp(newID, "", sID, date);
            comp.SetComplaint(text);   // validates + saves to DB
        }

        else {
            cout << "Invalid option.\n";
        }
    }
}
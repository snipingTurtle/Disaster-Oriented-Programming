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

void AdminComplaint::run() {
    while (true) {
        cout << "\nAdmin Complaint Panel\n";
        cout << "1: View All Complaints\n";
        cout << "2: Update Complaint Status\n";
        cout << "3: Delete a Complaint\n";
        cout << "4: Back\n";
        cout << "Choice: ";

        int c;
        cin >> c;
        cin.ignore();

        if (c == 4) break;

        else if (c == 1) {
            vector<Complaint> complaints = DatabaseHandler::LoadComplaints();
            if (complaints.empty()) {
                cout << "No complaints on record.\n";
            } else {
                for (auto& comp : complaints) comp.DisplayComplaint();
            }
        }

        else if (c == 2) {
            cout << "Enter Complaint ID to update: ";
            int id; cin >> id; cin.ignore();

            cout << "Enter new status (Pending/In Progress/Resolved): ";
            string status; getline(cin, status);

            // Load the matching complaint and update through the proper method
            vector<Complaint> complaints = DatabaseHandler::LoadComplaints();
            bool found = false;
            for (auto& comp : complaints) {
                if (comp.GetComplaintID() == id) {
                    AdminComplaint ac(comp.GetComplaintID(), comp.GetComplaintText(),
                                     comp.GetStudentID(), comp.GetDate());
                    ac.SetStatus(comp.GetStatus());
                    ac.UpdateStatus(status);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Complaint ID " << id << " not found.\n";
        }

        else if (c == 3) {
            cout << "Enter Complaint ID to delete: ";
            int id; cin >> id; cin.ignore();

            AdminComplaint ac;
            // We only need the ID for deletion — set it via a temporary object
            vector<Complaint> complaints = DatabaseHandler::LoadComplaints();
            bool found = false;
            for (auto& comp : complaints) {
                if (comp.GetComplaintID() == id) {
                    AdminComplaint ac2(comp.GetComplaintID(), comp.GetComplaintText(),
                                      comp.GetStudentID(), comp.GetDate());
                    ac2.DeleteComplaint();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Complaint ID " << id << " not found.\n";
        }

        else {
            cout << "Invalid option.\n";
        }
    }
}

AdminComplaint::~AdminComplaint() {}
#include "Provost.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "AssistantToProvost.hpp"
#include "complaint.hpp"
#include "database_handler.hpp"
#include "admin_complaint.hpp"
#include "notice_board.hpp"

using namespace std;

int Provost::provostCount = 0;
Provost::Provost(){}

Provost::Provost(int id, const string &name, int appointmentYear)
    : Admin(id, name, "Admin", "Provost", 10), appointmentYear(appointmentYear)
{
    if(provostCount >= 1)
    {
        throw runtime_error("Only ONE Provost is allowed in the system.");
    }
    provostCount++;
}

int Provost::getAppointmentYear() const
{
    return appointmentYear;
}

void Provost::assignShift(AssistantToProvost &assistant, const string &shift)
{
    assistant.setShift(shift);
    cout << "Provost assigned shift '" << shift << "' to " << assistant.role() << endl;
}

void Provost::updateComplaintStatus(Complaint &complaint, const string &status)
{
    complaint.UpdateStatus(status);
    DatabaseHandler::UpdateComplaintStatus(complaint.GetComplaintID(), status);
    cout << "Provost updated complaint ID " << complaint.GetComplaintID()
         << " to status: " << status << endl;
}

void Provost::updateNotice(int id, const string& title, const string& text)
{
    DatabaseHandler::UpdateNotice(id, title, text);
    cout << "Notice #" << id << " has been updated.\n";
}

void Provost::viewResidents() const
{
    cout << "Provost is viewing all residents." << endl;
}

string Provost::role() const
{
    return "Provost";
}

// ---------------------------------------------------------------------------
// Approve / reject pending users one by one
// ---------------------------------------------------------------------------
void Provost::approvePending()
{
    const string pending_file = "database/pending.csv";
    const string data_file    = "database/data.csv";

    ifstream pending(pending_file);
    if (!pending.is_open()) {
        cout << "Failed to open pending.csv!\n";
        return;
    }

    vector<string> lines;
    string line;
    while (getline(pending, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    pending.close();

    if (lines.empty()) {
        cout << "No pending users awaiting approval.\n";
        return;
    }

    vector<string> approved;
    vector<string> skipped;

    for (const string& entry : lines) {
        stringstream ss(entry);
        string name, email, pass, role;
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, pass, ',');
        getline(ss, role);

        cout << "\n--- Pending User ---\n";
        cout << "  Name  : " << name  << "\n";
        cout << "  Email : " << email << "\n";
        cout << "  Role  : " << role  << "\n";
        cout << "Approve? (y = approve / n = reject / s = skip for later): ";

        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            approved.push_back(entry);
            // Write stub row to role-specific CSV for first-time login detection
            string trimmed_role = role;
            size_t rs = trimmed_role.find_first_not_of(" \r\n\t");
            size_t re = trimmed_role.find_last_not_of(" \r\n\t");
            if (rs != string::npos) trimmed_role = trimmed_role.substr(rs, re - rs + 1);

            if (trimmed_role == "student") {
                ofstream stub("database/students.csv", ios::app);
                if (stub.is_open()) {
                    // Format: name,email,pass,   (id empty = first time login)
                    stub << name << "," << email << "," << pass << ",\n";
                    stub.close();
                }
            } else if (trimmed_role == "faculty" || trimmed_role == "part time faculty") {
                ofstream stub("database/faculty.csv", ios::app);
                if (stub.is_open()) {
                    // Format: name,email,pass,   (id empty = first time login)
                    stub << name << "," << email << "," << pass << ",\n";
                    stub.close();
                }
            }
            cout << "Approved.\n";
        } else if (choice == 'n' || choice == 'N') {
            cout << "Rejected and removed from queue.\n";
            // discarded — not added anywhere
        } else {
            skipped.push_back(entry);
            cout << "Skipped (kept in pending).\n";
        }
    }

    if (!approved.empty()) {
        // Count existing rows to determine next serial ID
        int next_id = 1;
        {
            ifstream count_f(data_file);
            string count_line;
            while (getline(count_f, count_line)) {
                if (!count_line.empty()) next_id++;
            }
        }
        ofstream data(data_file, ios::app);
        if (!data.is_open()) {
            cout << "Failed to open data.csv!\n";
            return;
        }
        for (const string& a : approved) {
            data << next_id << "," << a << "\n";
            next_id++;
        }
        data.close();
        cout << "\n" << approved.size() << " user(s) approved and added.\n";
    }

    // Rewrite pending.csv with only skipped entries
    ofstream clear_pending(pending_file, ios::trunc);
    for (const string& s : skipped) clear_pending << s << "\n";
    clear_pending.close();
}

// ---------------------------------------------------------------------------
// Notice board management
// ---------------------------------------------------------------------------
void Provost::manageNotices()
{
    while (true) {
        cout << "\n--- Notice Board ---\n";
        cout << "1: Post a new notice\n";
        cout << "2: View all notices\n";
        cout << "3: Update an existing notice\n";
        cout << "4: Back\n";
        cout << "Choice: ";

        int c;
        cin >> c;
        cin.ignore();

        if (c == 4) break;

        else if (c == 1) {
            vector<NoticeBoard> existing = DatabaseHandler::LoadNotices();
            int newID = existing.empty() ? 1 : existing.back().GetNoticeID() + 1;

            string title, text;
            cout << "Title   : "; getline(cin, title);
            cout << "Message : "; getline(cin, text);

            // Auto-generate timestamp
            time_t now = time(nullptr);
            char buf[32];
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
            string timestamp(buf);

            NoticeBoard nb(newID, "", "", getName(), timestamp);
            // postNotice sets all fields and calls SetAnnouncement, which saves to DB
            postNotice(nb, title, text, timestamp);
        }

        else if (c == 2) {
            vector<NoticeBoard> notices = DatabaseHandler::LoadNotices();
            if (notices.empty()) {
                cout << "No notices found.\n";
            } else {
                for (auto& n : notices) n.ViewNotice();
            }
        }

        else if (c == 3) {
            cout << "Enter Notice ID to update: ";
            int id; cin >> id; cin.ignore();

            string title, text;
            cout << "New Title   : "; getline(cin, title);
            cout << "New Message : "; getline(cin, text);

            updateNotice(id, title, text);
        }

        else {
            cout << "Invalid option.\n";
        }
    }
}

// ---------------------------------------------------------------------------
// Main interactive loop
// ---------------------------------------------------------------------------
void Provost::run()
{
    while (true) {
        cout << "\nProvost Panel\n";
        cout << "1: Complaints\n";
        cout << "2: Approve Users\n";
        cout << "3: Notices\n";
        cout << "4: Logout\n";
        cout << "Choice: ";

        int c;
        cin >> c;

        if (c == 4) {
            cout << "Logging out from Provost Level\n";
            break;
        }
        else if (c == 2) {
            approvePending();
        }
        else if (c == 1) {
            AdminComplaint AC;
            AC.run();
        }
        else if (c == 3) {
            manageNotices();
        }
        else {
            cout << "Invalid option.\n";
        }
    }
}

Provost::~Provost()
{
    provostCount--;
}
#include "Provost.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include "AssistantToProvost.hpp"
#include "complaint.hpp"
#include "database_handler.hpp"
#include "admin_complaint.hpp"
#include "notice_board.hpp"
#include "message.hpp"

using namespace std;

// Returns the data.csv serial ID for this user (used as messaging ID)
static int getDataId(const string& loginName) {
    ifstream f("database/data.csv");
    string line;
    while (getline(f, line)) {
        stringstream ss(line);
        string id_str, n, e;
        getline(ss, id_str, ',');
        getline(ss, n, ',');
        getline(ss, e, ',');
        if (n == loginName || e == loginName)
            return stoi(id_str);
    }
    return 0;
}

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

void Provost::setLoginName(const string& n)
{
    loginName = n;
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
        cout << "4: Send Message\n";
        cout << "5: Read Messages\n";
        cout << "6: Logout\n";
        cout << "Choice: ";

        int c;
        cin >> c;

        if (c == 6) {
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
        else if (c == 4) {
            int senderDataId = getDataId(loginName);
            int destination;
            cout << "Enter the recipient's data ID: ";
            cin >> destination;
            cin.ignore();
            string content;
            cout << "Enter your message (press Enter then ~ to finish):\n";
            getline(cin, content, '~');
            cin.ignore();
            Message msg(senderDataId, destination, content);
            msg.Send();
            cout << "Message sent successfully!\n";
        }
        else if (c == 5) {
            int myId = getDataId(loginName);
            DatabaseHandler::LoadMessages();
            ifstream inFile("database/messages.csv");
            if (!inFile) { cout << "No messages.\n"; }
            else {
                cout << "\n1: Read New Messages\n2: View Read Messages\nChoice: ";
                int sub; cin >> sub;

                Message m;
                vector<int> readIds;
                bool found = false;
                // Re-open for fresh read
                inFile.close();
                inFile.open("database/messages.csv");
                while (inFile >> m) {
                    bool isUnread = m.getUnread();
                    if (m.getReciever() == myId && ((sub == 1 && isUnread) || (sub == 2 && !isUnread))) {
                        cout << m;
                        if (sub == 1) readIds.push_back(m.getMessageID());
                        found = true;
                    }
                }
                inFile.close();
                if (!found) cout << (sub == 1 ? "No new messages.\n" : "No previously read messages.\n");

                if (!readIds.empty()) {
                    ifstream rf("database/messages.csv");
                    vector<string> lines;
                    string ln;
                    while (getline(rf, ln)) lines.push_back(ln);
                    rf.close();

                    ofstream wf("database/messages.csv", ios::trunc);
                    for (auto& l : lines) {
                        stringstream ss(l);
                        string id_s, sen, rec, rest;
                        getline(ss, id_s, ',');
                        getline(ss, sen, ',');
                        getline(ss, rec, ',');
                        getline(ss, rest);

                        size_t last = rest.rfind(',');
                        size_t second_last = rest.rfind(',', last - 1);
                        string unrd    = rest.substr(last + 1);
                        string ts      = rest.substr(second_last + 1, last - second_last - 1);
                        string content = rest.substr(0, second_last);

                        int msgId = stoi(id_s);
                        bool nowUnread = (unrd == "1" || unrd == "true");
                        for (int rid : readIds)
                            if (rid == msgId) { nowUnread = false; break; }
                        wf << id_s << "," << sen << "," << rec << ","
                           << content << "," << ts << "," << nowUnread << "\n";
                    }
                    wf.close();
                }
            }
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
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include "../include/student.hpp"
#include "../include/complaint.hpp"
#include "../include/notice_board.hpp"
#include "../include/database_handler.hpp"
#include "../include/message.hpp"
#define nl '\n'
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

// ================== GETTER IMPLEMENTATIONS ==================

int student::getId() const { 
    return id; 
}

int student::getRoomNumber() const { 
    return roomNumber; 
}

string student::getHall() const { 
    return hall; 
}

string student::getPassword() const { 
    return password; 
}

string student::getEmail() const { 
    return email; 
}

int student::getUnreadMessages() const { 
    return unreadMessages; 
}

// ================== SETTER IMPLEMENTATIONS ==================

void student::setId(int newId) { 
    id = newId; 
}

void student::setRoomNumber(int newRoomNumber) { 
    roomNumber = newRoomNumber; 
}

void student::setHall(const string& newHall) { 
    hall = newHall; 
}

void student::setPassword(const string& newPassword) { 
    password = newPassword; 
}

void student::setEmail(const string& newEmail) { 
    email = newEmail; 
}

void student::setUnreadMessages(int newUnreadMessages) { 
    unreadMessages = newUnreadMessages; 
}
void student::getCountOfUnreadMessages(){
    int myId = getDataId(loginName);
    DatabaseHandler::LoadMessages();
    int count = 0;
    ifstream inFile("database/messages.csv");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id_s, sender_s, recv_s, content, time_s, unread_s;
        getline(ss, id_s, ',');
        getline(ss, sender_s, ',');
        getline(ss, recv_s, ',');
        if (stoi(recv_s) == myId) {
            getline(ss, content, ',');
            getline(ss, time_s, ',');
            getline(ss, unread_s);
            if (unread_s == "1" || unread_s == "true") count++;
        }
    }
    unreadMessages = count;
    cout << unreadMessages << " unread message(s)\n";
}

void student::readMessages(){
    int myId = getDataId(loginName);
    DatabaseHandler::LoadMessages();

    ifstream inFile("database/messages.csv");
    if (!inFile) { cout << "No messages.\n"; return; }

    Message m;
    vector<int> readIds;
    bool found = false;
    while (inFile >> m) {
        if (m.getReciever() == myId && m.getUnread()) {
            cout << m;
            readIds.push_back(m.getMessageID());
            found = true;
        }
    }
    inFile.close();
    if (!found) { cout << "No new messages.\n"; return; }

    // Mark as read in DB map and rewrite file
    for (int rid : readIds)
        DatabaseHandler::MarkMessageRead(rid);

    // Rewrite messages.csv with updated read status
    DatabaseHandler::LoadMessages(); // reload to get updated state
    // We need to rewrite the file — reload fresh then rewrite
    {
        // Read all lines, flip unread flag for marked IDs
        ifstream rf("database/messages.csv");
        vector<string> lines;
        string ln;
        while (getline(rf, ln)) lines.push_back(ln);
        rf.close();

        ofstream wf("database/messages.csv", ios::trunc);
        for (auto& l : lines) {
            stringstream ss(l);
            string id_s, sen, rec, content, ts, unrd;
            getline(ss, id_s, ',');
            getline(ss, sen, ',');
            getline(ss, rec, ',');

            // rebuild content (quoted)
            string rest;
            getline(ss, rest);
            // find the last two comma-separated fields (ts, unrd)
            // content may contain commas so parse from the end
            size_t last = rest.rfind(',');
            size_t second_last = rest.rfind(',', last - 1);
            unrd = rest.substr(last + 1);
            ts   = rest.substr(second_last + 1, last - second_last - 1);
            content = rest.substr(0, second_last);

            int msgId = stoi(id_s);
            bool wasUnread = (unrd == "1" || unrd == "true");
            bool nowUnread = wasUnread;
            for (int rid : readIds) {
                if (rid == msgId) { nowUnread = false; break; }
            }
            wf << id_s << "," << sen << "," << rec << ","
               << content << "," << ts << "," << nowUnread << "\n";
        }
        wf.close();
    }
}

void student::writeMessage(){
    int senderDataId = getDataId(loginName);
    int destination;
    cout << "Enter the recipient's data ID: ";
    cin >> destination;
    cin.ignore();
    string content;
    cout << "Enter your message (press ~ to finish):\n";
    getline(cin, content, '~');
    cin.ignore();

    Message msg(senderDataId, destination, content);
    msg.Send();
    cout << "Message sent successfully!\n";
}

void student::readReadMessagesFile(){
    int myId = getDataId(loginName);
    DatabaseHandler::LoadMessages();

    ifstream inFile("database/messages.csv");
    if (!inFile) { cout << "No messages.\n"; return; }

    Message m;
    bool found = false;
    while (inFile >> m) {
        if (m.getReciever() == myId && !m.getUnread()) {
            cout << m;
            found = true;
        }
    }
    if (!found) cout << "No previously read messages.\n";
}
void Student(){
    cout << "Student data" << nl;
    //student s1(129, "Zahin", 159154, "O+", 39629, 123, "South Hall");
    //s1.displayDetails();
}

void student::setLoginName(const string& n) {
    loginName = n;
}

bool student::checkFirstTimeLogin() {
    string file_name = "database/students.csv";
    ifstream f(file_name);
    if (!f.is_open()) return false;
    string line;
    while (getline(f, line)) {
        stringstream ss(line);
        string name, em, pass, sid;
        getline(ss, name, ',');
        getline(ss, em, ',');
        getline(ss, pass, ',');
        getline(ss, sid, ',');
        if (name == loginName || em == loginName) {
            f.close();
            // If id field is empty, it's first time
            return sid.empty();
        }
    }
    f.close();
    return false;
}

void student::firstTimeLogin() {
    cout << "\n--- First Time Login: Please complete your profile ---\n";
    int sid, phone, emergencyC, room;
    string bloodGroup, hall_name;
    cout << "Enter your Student ID: "; cin >> sid;
    cout << "Enter your Phone Number: "; cin >> phone;
    cout << "Enter your Emergency Contact Number: "; cin >> emergencyC;
    cout << "Enter your Room Number: "; cin >> room;
    cout << "Enter your Blood Group: "; cin >> bloodGroup;
    cout << "Enter your Hall Name: "; cin >> hall_name;

    // Update in-memory
    setId(sid);
    setPhoneNumber(phone);
    setEmergencyContact(emergencyC);
    setRoomNumber(room);
    setBloodGroup(bloodGroup);
    setHall(hall_name);

    // Rewrite students.csv updating this student's row
    string file_name = "database/students.csv";
    ifstream f(file_name);
    vector<string> lines;
    string line;
    while (getline(f, line)) lines.push_back(line);
    f.close();

    ofstream out(file_name, ios::trunc);
    for (auto& l : lines) {
        stringstream ss(l);
        string name, em, pass, old_sid;
        getline(ss, name, ',');
        getline(ss, em, ',');
        getline(ss, pass, ',');
        getline(ss, old_sid, ',');
        if ((name == loginName || em == loginName) && old_sid.empty()) {
            out << name << "," << em << "," << pass << ","
                << sid << "," << phone << "," << emergencyC << ","
                << room << "," << bloodGroup << "," << hall_name << "\n";
        } else {
            out << l << "\n";
        }
    }
    out.close();
    cout << "Profile saved successfully!\n";
}

void student::run(){
    if (checkFirstTimeLogin()) {
        firstTimeLogin();
    }
    while(1){
        cout << "\nStudent Panel\n";
        cout << "1: View Notices\n";
        cout << "2: Give Student Announcement\n";
        cout << "3: Send Message\n";
        cout << "4: Read Messages\n";
        cout << "5: Set Complaint\n";
        cout << "6: Exit\n";

        int c;
        cin >> c;

        if(c == 6) {
            cout << "Logging out from Student Level\n";
            break;
        }
        else if(c == 1) {
            vector<NoticeBoard> notices = DatabaseHandler::LoadNotices();
            if (notices.empty()) {
                cout << "No notices found.\n";
            } else {
                for (auto& n : notices) n.ViewNotice();
            }
        }
        else if(c == 2) {
            vector<NoticeBoard> existing = DatabaseHandler::LoadNotices();
            int newID = existing.empty() ? 1 : existing.back().GetNoticeID() + 1;

            string title, text;
            cin.ignore();
            cout << "Title   : "; getline(cin, title);
            cout << "Message : "; getline(cin, text);

            time_t now = time(nullptr);
            char buf[32];
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
            string timestamp(buf);

            NoticeBoard nb(newID, title, text, loginName, timestamp);
            nb.SetAnnouncement(text);
        }
        else if(c == 3) {
            writeMessage();
        }
        else if(c == 4) {
            cout << "\n1: Read New Messages\n2: View Read Messages\nChoice: ";
            int sub; cin >> sub;
            if (sub == 1) readMessages();
            else if (sub == 2) readReadMessagesFile();
            else cout << "Invalid option.\n";
        }
        else if(c == 5) {
            Complaint comp;
            comp.run(id);
        }
        else {
            cout << "Invalid option.\n";
        }
    }
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <limits>
#include "../include/faculty.hpp"
#include "../include/complaint.hpp"
#include "../include/notice_board.hpp"
#include "../include/database_handler.hpp"
#define nl '\n'
using namespace std;

// ================== GETTER IMPLEMENTATIONS ==================

int faculty::getId() const { 
    return id; 
}

int faculty::getRoomNumber() const { 
    return roomNumber; 
}

string faculty::getHall() const { 
    return hall; 
}

string faculty::getPassword() const { 
    return password; 
}

string faculty::getEmail() const { 
    return email; 
}

int faculty::getUnreadMessages() const { 
    return unreadMessages; 
}

// ================== SETTER IMPLEMENTATIONS ==================

void faculty::setId(int newId) { 
    id = newId; 
}

void faculty::setRoomNumber(int newRoomNumber) { 
    roomNumber = newRoomNumber; 
}

void faculty::setHall(const string& newHall) { 
    hall = newHall; 
}

void faculty::setPassword(const string& newPassword) { 
    password = newPassword; 
}

void faculty::setEmail(const string& newEmail) { 
    email = newEmail; 
}

void faculty::setUnreadMessages(int newUnreadMessages) { 
    unreadMessages = newUnreadMessages; 
}
void faculty::getCountOfUnreadMessages(){
    string fileName = "../Messages/" + to_string(id) + "Unread.txt";
    ifstream inFile(fileName);
    string line;
    while (getline(inFile, line)) {
        unreadMessages++;
    }
    cout << unreadMessages << "messages" << "\n";
}
void faculty::readMessages(){
    string fileName = "../Messages/" + to_string(id) + "Unread.txt";
    ifstream inFile(fileName);
    string fileName2 = "../Messages/" + to_string(id) + "Read.txt";
    ofstream outFile;
    outFile.open(fileName2, ios::app);
    string line;
    while (getline(inFile, line)) {
        cout << line << "\n";
        outFile << line << "\n";
    }
    inFile.close();
    outFile.close();
    outFile.open(fileName, ios::trunc);
    if (outFile.is_open()) {
        cout << "File '" << fileName << "' has been successfully cleared.\n";
        outFile.close();
    } else {
        cerr << "Error: Could not open the file to clear it.\n";
    }
}
void faculty::writeMessage(){
    int destination;
    cout << "Enter the id of recipient: ";
    cin >> destination;
    cin.ignore();
    string fileName = "../Messages/" + to_string(destination) + "Unread.txt";
    ofstream outFile;
    outFile.open(fileName, ios::app);
    string message;
    cout << "Enter your message, press ~ and enter when done: " << "\n";
    getline(cin, message, '~');
    outFile << message << "\n";
    cout << "Message Sent Successfully!" << "\n";
    outFile.close();
}
void faculty::readReadMessagesFile(){
    string fileName = "../Messages/" + to_string(id) + "Read.txt";
    ifstream inFile(fileName);
    string line;
    while (getline(inFile, line)) {
        cout << line << "\n";
    }
    inFile.close();
}
void Faculty(){
    cout << "Faculty data" << nl;
    //faculty f1(129, "Zahin", 159154, "O+", 39629, 123, "South Hall");
    //f1.displayDetails();
}

void faculty::setLoginName(const string& n) {
    loginName = n;
}

bool faculty::checkFirstTimeLogin() {
    string file_name = "database/faculty.csv";
    ifstream f(file_name);
    if (!f.is_open()) return false;
    string line;
    while (getline(f, line)) {
        stringstream ss(line);
        string name, em, pass, fid;
        getline(ss, name, ',');
        getline(ss, em, ',');
        getline(ss, pass, ',');
        getline(ss, fid, ',');
        if (name == loginName || em == loginName) {
            f.close();
            // If id field is empty, it's first time
            return fid.empty();
        }
    }
    f.close();
    return false;
}

void faculty::firstTimeLogin() {
    cout << "\n--- First Time Login: Please complete your profile ---\n";
    int fid, phone, emergencyC, room;
    string bloodGroup, hall_name;
    cout << "Enter your Faculty ID: "; cin >> fid;
    cout << "Enter your Phone Number: "; cin >> phone;
    cout << "Enter your Emergency Contact Number: "; cin >> emergencyC;
    cout << "Enter your Room Number: "; cin >> room;
    cout << "Enter your Blood Group: "; cin >> bloodGroup;
    cout << "Enter your Hall Name: "; cin >> hall_name;

    // Update in-memory
    setId(fid);
    setPhoneNumber(phone);
    setEmergencyContact(emergencyC);
    setRoomNumber(room);
    setBloodGroup(bloodGroup);
    setHall(hall_name);

    // Rewrite faculty.csv updating this faculty's row
    string file_name = "database/faculty.csv";
    ifstream f(file_name);
    vector<string> lines;
    string line;
    while (getline(f, line)) lines.push_back(line);
    f.close();

    ofstream out(file_name, ios::trunc);
    for (auto& l : lines) {
        stringstream ss(l);
        string name, em, pass, old_fid;
        getline(ss, name, ',');
        getline(ss, em, ',');
        getline(ss, pass, ',');
        getline(ss, old_fid, ',');
        if ((name == loginName || em == loginName) && old_fid.empty()) {
            out << name << "," << em << "," << pass << ","
                << fid << "," << phone << "," << emergencyC << ","
                << room << "," << bloodGroup << "," << hall_name << "\n";
        } else {
            out << l << "\n";
        }
    }
    out.close();
    cout << "Profile saved successfully!\n";
}

void faculty::run(){
    if (checkFirstTimeLogin()) {
        firstTimeLogin();
    }
    while(1){
        cout << "\nFaculty Panel\n";
        cout << "1: View Notices\n";
        cout << "2: Give General Announcement\n";
        cout << "3: Send Message\n";
        cout << "4: Read Messages\n";
        cout << "5: Set Complaint\n";
        cout << "6: Exit\n";

        int c;
        cin >> c;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option.\n";
            continue;
        }

        if(c == 6) {
            cout << "Logging out from Faculty Level\n";
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
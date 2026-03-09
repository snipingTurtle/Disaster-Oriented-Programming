#include "database_handler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// This will be implemented in subsequent commits as per the roadmap
void DatabaseHandler::SaveComplaint(const Complaint& complaint) {
    ofstream outFile("complaints.txt", ios::app);
    if (outFile.is_open()) {
        outFile << complaint.GetComplaintID() << ","
                << complaint.GetStudentID() << ","
                << complaint.GetDate() << ","
                << complaint.GetStatus() << ","
                << complaint.GetComplaintText() << endl;
        outFile.close();
    } else {
        cerr << "Error: Could not open complaints.txt for writing." << endl;
    }
}

vector<Complaint> DatabaseHandler::LoadComplaints() {
    vector<Complaint> complaints;
    ifstream inFile("complaints.txt");
    string line;
    
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id_str, sID_str, date, status, text;
            
            if (getline(ss, id_str, ',') &&
                getline(ss, sID_str, ',') &&
                getline(ss, date, ',') &&
                getline(ss, status, ',') &&
                getline(ss, text)) {
                
                Complaint c(stoi(id_str), text, stoi(sID_str), date);
                c.SetStatus(status);
                complaints.push_back(c);
            }
        }
        inFile.close();
    }
    return complaints;
}

void DatabaseHandler::SaveNotice(const NoticeBoard& notice) {
    ofstream outFile("notices.txt", ios::app);
    if (outFile.is_open()) {
        outFile << notice.GetNoticeID() << ","
                << notice.GetAuthor() << ","
                << notice.GetTimestamp() << ","
                << notice.GetTitle() << ","
                << notice.GetAnnouncement() << endl;
        outFile.close();
    } else {
        cerr << "Error: Could not open notices.txt for writing." << endl;
    }
}
vector<NoticeBoard> DatabaseHandler::LoadNotices() { return {}; }

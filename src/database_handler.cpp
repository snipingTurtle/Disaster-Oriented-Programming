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

vector<Complaint> DatabaseHandler::LoadComplaints() { return {}; }

void DatabaseHandler::SaveNotice(const NoticeBoard& notice) {}
vector<NoticeBoard> DatabaseHandler::LoadNotices() { return {}; }

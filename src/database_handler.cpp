#include "database_handler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <filesystem>          // ← added for create_directories

using namespace std;

static const string COMPLAINTS_FILE = "database/complaints.csv";
static const string CSV_HEADER      = "ComplaintID,StudentID,Date,Status,ComplaintText";

// Creates database/ dir and header row if the file doesn't exist yet
static void EnsureComplaintsFile() {
    filesystem::create_directories("database");
    ifstream check(COMPLAINTS_FILE);
    if (!check.good()) {
        ofstream init(COMPLAINTS_FILE);
        init << CSV_HEADER << "\n";
    }
}

void DatabaseHandler::SaveComplaint(const Complaint &complaint)
{
    EnsureComplaintsFile();
    ofstream outFile(COMPLAINTS_FILE, ios::app);
    if (outFile.is_open())
    {
        outFile << complaint.GetComplaintID() << ","
                << complaint.GetStudentID() << ","
                << complaint.GetDate() << ","
                << complaint.GetStatus() << ","
                << complaint.GetComplaintText() << endl;
        outFile.close();
    }
    else
    {
        cerr << "Error: Could not open " << COMPLAINTS_FILE << " for writing." << endl;
    }
}

vector<Complaint> DatabaseHandler::LoadComplaints()
{
    EnsureComplaintsFile();
    vector<Complaint> complaints;
    ifstream inFile(COMPLAINTS_FILE);
    string line;

    if (inFile.is_open())
    {
        getline(inFile, line); // skip header row
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string id_str, sID_str, date, status, text;

            if (getline(ss, id_str, ',') &&
                getline(ss, sID_str, ',') &&
                getline(ss, date, ',') &&
                getline(ss, status, ',') &&
                getline(ss, text))
            {
                Complaint c(stoi(id_str), text, stoi(sID_str), date);
                c.SetStatus(status);
                complaints.push_back(c);
            }
        }
        inFile.close();
    }
    return complaints;
}

void DatabaseHandler::UpdateComplaintStatus(int id, const string &newStatus)
{
    vector<Complaint> complaints = LoadComplaints();
    ofstream outFile(COMPLAINTS_FILE); // Overwrite
    if (outFile.is_open())
    {
        outFile << CSV_HEADER << "\n"; // re-write header
        for (auto &c : complaints)
        {
            if (c.GetComplaintID() == id)
                c.SetStatus(newStatus);

            outFile << c.GetComplaintID() << ","
                    << c.GetStudentID() << ","
                    << c.GetDate() << ","
                    << c.GetStatus() << ","
                    << c.GetComplaintText() << endl;
        }
        outFile.close();
    }
}

void DatabaseHandler::DeleteComplaint(int id)          // ← new function
{
    vector<Complaint> complaints = LoadComplaints();
    ofstream outFile(COMPLAINTS_FILE); // Overwrite
    if (outFile.is_open())
    {
        outFile << CSV_HEADER << "\n"; // re-write header
        for (auto &c : complaints)
        {
            if (c.GetComplaintID() != id) // skip the deleted one
            {
                outFile << c.GetComplaintID() << ","
                        << c.GetStudentID() << ","
                        << c.GetDate() << ","
                        << c.GetStatus() << ","
                        << c.GetComplaintText() << endl;
            }
        }
        outFile.close();
    }
}

void DatabaseHandler::SaveNotice(const NoticeBoard &notice)
{
    ofstream outFile("notices.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << notice.GetNoticeID() << ","
                << notice.GetAuthor() << ","
                << notice.GetTimestamp() << ","
                << notice.GetTitle() << ","
                << notice.GetAnnouncement() << endl;
        outFile.close();
    }
    else
    {
        cerr << "Error: Could not open notices.txt for writing." << endl;
    }
}

vector<NoticeBoard> DatabaseHandler::LoadNotices()
{
    vector<NoticeBoard> notices;
    ifstream inFile("notices.txt");
    string line;

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string id_str, author, ts, title, announcement;

            if (getline(ss, id_str, ',') &&
                getline(ss, author, ',') &&
                getline(ss, ts, ',') &&
                getline(ss, title, ',') &&
                getline(ss, announcement))
            {
                NoticeBoard n(stoi(id_str), title, announcement, author, ts);
                notices.push_back(n);
            }
        }
        inFile.close();
    }
    return notices;
}

void DatabaseHandler::UpdateNotice(int id, const string& newTitle, const string& newText) {
    vector<NoticeBoard> notices = LoadNotices();
    ofstream outFile("notices.txt");
    if (outFile.is_open()) {
        for (auto& n : notices) {
            if (n.GetNoticeID() == id) {
                n.SetTitle(newTitle);
                n.SetAnnouncement(newText);
            }
            outFile << n.GetNoticeID() << "," << n.GetAuthor() << "," << n.GetTimestamp() << ","
                    << n.GetTitle() << "," << n.GetAnnouncement() << endl;
        }
        outFile.close();
    }
}

unordered_map<int, Message> DatabaseHandler::messageDB;

string escapeCSV(const string &s)
{
    string result;
    for (char c : s)
    {
        if (c == '"')
            result += "\"\"";
        else
            result += c;
    }
    return result;
}

void DatabaseHandler::SaveMessage(const Message &message)
{
    ofstream outFile("messages.csv", ios::app);
    if (!outFile)
        throw runtime_error("Could not open messages.csv");

    time_t t = chrono::system_clock::to_time_t(message.getTime());

    outFile << message.getMessageID() << ","
            << message.getSender() << ","
            << message.getReciever() << ","
            << '"' << escapeCSV(message.getContent()) << '"' << ","
            << t << ","
            << message.getUnread()
            << endl;

    outFile.close();
}

void DatabaseHandler::LoadMessages()
{
    ifstream inFile("messages.csv");
    if(!inFile) return;

    Message m;
    while (inFile >> m)
    {
        messageDB[m.getMessageID()] = m;
    }
}

Message DatabaseHandler::GetMessage(const int &message_id)
{
    if (messageDB.find(message_id) == messageDB.end())
        throw runtime_error("Message not found");
    return messageDB[message_id];
}

void DatabaseHandler::MarkMessageRead(const int &message_id)
{
    if (messageDB.find(message_id) != messageDB.end())
    {
        messageDB[message_id].MarkAsRead();
    }
}
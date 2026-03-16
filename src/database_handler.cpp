#include "database_handler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <chrono>
#include <ctime>

using namespace std;

void DatabaseHandler::SaveComplaint(const Complaint &complaint)
{
    ofstream outFile("complaints.txt", ios::app);
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
        cerr << "Error: Could not open complaints.txt for writing." << endl;
    }
}

vector<Complaint> DatabaseHandler::LoadComplaints()
{
    vector<Complaint> complaints;
    ifstream inFile("complaints.txt");
    string line;

    if (inFile.is_open())
    {
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
    ofstream outFile("complaints.txt"); // Overwrite
    if (outFile.is_open())
    {
        for (auto &c : complaints)
        {
            if (c.GetComplaintID() == id)
            {
                c.SetStatus(newStatus);
            }
            outFile << c.GetComplaintID() << ","
                    << c.GetStudentID() << ","
                    << c.GetDate() << ","
                    << c.GetStatus() << ","
                    << c.GetComplaintText() << endl;
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

// Database For Messages

unordered_map<int, Message> DatabaseHandler::messageDB;

void DatabaseHandler::SaveMessage(const Message &message)
{
    ofstream outFile("messages.csv", ios::app);

    if (!outFile)
        throw runtime_error("Could not open messages.csv");

    time_t t = chrono::system_clock::to_time_t(message.getTime());

    outFile << message.getMessageID() << ","
            << message.getSender() << ","
            << message.getReciever() << ","
            << message.getContent() << ","
            << t << ","
            << message.getUnread()
            << endl;

    outFile.close();
}

void DatabaseHandler::LoadMessages()
{
    ifstream inFile("messages.csv");
    string line;

    while (getline(inFile, line))
    {
        stringstream ss(line);

        string id, sender, receiver, content, time, unread;

        getline(ss, id, ',');
        getline(ss, sender, ',');
        getline(ss, receiver, ',');
        getline(ss, content, ',');
        getline(ss, time, ',');
        getline(ss, unread, ',');

        int msgID = stoi(id);

        chrono::system_clock::time_point tp =
            chrono::system_clock::from_time_t(stoll(time));

        Message m(
            msgID,
            stoi(sender),
            stoi(receiver),
            content,
            tp,
            unread == "1");

        messages[msgID] = m;
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

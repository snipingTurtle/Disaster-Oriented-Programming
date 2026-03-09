#include "notice_board.hpp"
#include "database_handler.hpp"
#include <iostream>

using namespace std;

NoticeBoard::NoticeBoard() : noticeID(0), title(""), announcement(""), author(""), timestamp("") {}

NoticeBoard::NoticeBoard(int id, const string& t, const string& a, const string& auth, const string& ts)
    : noticeID(id), title(t), announcement(a), author(auth), timestamp(ts) {}

int NoticeBoard::GetNoticeID() const { return noticeID; }
string NoticeBoard::GetTitle() const { return title; }
string NoticeBoard::GetAnnouncement() const { return announcement; }
string NoticeBoard::GetAuthor() const { return author; }
string NoticeBoard::GetTimestamp() const { return timestamp; }

void NoticeBoard::SetTitle(const string& t) { title = t; }
void NoticeBoard::SetAnnouncement(const string& a) { 
    announcement = a; 
    DatabaseHandler::SaveNotice(*this);
    cout << "Success: Announcement has been posted to the NoticeBoard." << endl;
}
void NoticeBoard::SetAuthor(const string& auth) { author = auth; }
void NoticeBoard::SetTimestamp(const string& ts) { timestamp = ts; }

void NoticeBoard::ViewNotice() const {
    cout << "\n--------------------------------------------\n";
    cout << "              NOTICE BOARD                  \n";
    cout << "--------------------------------------------\n";
    cout << "  Title      : " << title << "\n";
    cout << "  Author     : " << author << "\n";
    cout << "  Date       : " << timestamp << "\n";
    cout << "--------------------------------------------\n";
    cout << "  " << announcement << "\n";
    cout << "--------------------------------------------\n";
}

NoticeBoard::~NoticeBoard() {}

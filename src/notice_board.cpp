#include "notice_board.hpp"

NoticeBoard::NoticeBoard() : noticeID(0), title(""), announcement(""), author(""), timestamp("") {}

NoticeBoard::NoticeBoard(int id, const string& t, const string& a, const string& auth, const string& ts)
    : noticeID(id), title(t), announcement(a), author(auth), timestamp(ts) {}

int NoticeBoard::GetNoticeID() const { return noticeID; }
string NoticeBoard::GetTitle() const { return title; }
string NoticeBoard::GetAnnouncement() const { return announcement; }
string NoticeBoard::GetAuthor() const { return author; }
string NoticeBoard::GetTimestamp() const { return timestamp; }

void NoticeBoard::SetTitle(const string& t) { title = t; }
void NoticeBoard::SetAnnouncement(const string& a) { announcement = a; }
void NoticeBoard::SetAuthor(const string& auth) { author = auth; }
void NoticeBoard::SetTimestamp(const string& ts) { timestamp = ts; }

NoticeBoard::~NoticeBoard() {}

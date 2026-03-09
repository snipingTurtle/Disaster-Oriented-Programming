#ifndef NOTICE_BOARD_HPP
#define NOTICE_BOARD_HPP

#include <string>

using namespace std;

class NoticeBoard {
private:
    int noticeID;
    string title;
    string announcement;
    string author;
    string timestamp;

public:
    NoticeBoard();
    NoticeBoard(int id, const string& t, const string& a, const string& auth, const string& ts);

    // Getters
    int GetNoticeID() const;
    string GetTitle() const;
    string GetAnnouncement() const;
    string GetAuthor() const;
    string GetTimestamp() const;

    // Setters
    void SetTitle(const string& t);
    void SetAnnouncement(const string& a);
    void SetAuthor(const string& auth);
    void SetTimestamp(const string& ts);

    void ViewNotice() const;
    
    ~NoticeBoard();
};

#endif

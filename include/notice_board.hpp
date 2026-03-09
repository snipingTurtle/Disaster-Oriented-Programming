#ifndef NOTICE_BOARD_HPP
#define NOTICE_BOARD_HPP

#include <string>

using namespace std;

class NoticeBoard {
private:
    int noticeID;
    string announcement;

public:
    NoticeBoard();
    ~NoticeBoard();
};

#endif

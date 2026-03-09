#ifndef DATABASE_HANDLER_HPP
#define DATABASE_HANDLER_HPP

#include <vector>
#include <string>
#include "complaint.hpp"
#include "notice_board.hpp"

class DatabaseHandler {
public:
    // Complaint Database Operations
    static void SaveComplaint(const Complaint& complaint);
    static vector<Complaint> LoadComplaints();

    // NoticeBoard Database Operations
    static void SaveNotice(const NoticeBoard& notice);
    static vector<NoticeBoard> LoadNotices();
};

#endif

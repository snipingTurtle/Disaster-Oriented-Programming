#ifndef DATABASE_HANDLER_HPP
#define DATABASE_HANDLER_HPP

#include <vector>
#include <string>
#include "complaint.hpp"
#include "notice_board.hpp"
#include "message.hpp"

class DatabaseHandler {
public:
    // Complaint Database Operations
    static void SaveComplaint(const Complaint& complaint);
    static vector<Complaint> LoadComplaints();
    static void UpdateComplaintStatus(int id, const string& newStatus);

    // NoticeBoard Database Operations
    static void SaveNotice(const NoticeBoard& notice);
    static vector<NoticeBoard> LoadNotices();

    // Message Database Operations
    static void SaveMessage(const Message &message);
    static vector<Message> LoadMessages();
    static Message GetMessage(const int &message_id);
};

#endif

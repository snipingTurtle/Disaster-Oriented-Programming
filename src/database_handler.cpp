#include "database_handler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// This will be implemented in subsequent commits as per the roadmap
void DatabaseHandler::SaveComplaint(const Complaint& complaint) {}
vector<Complaint> DatabaseHandler::LoadComplaints() { return {}; }

void DatabaseHandler::SaveNotice(const NoticeBoard& notice) {}
vector<NoticeBoard> DatabaseHandler::LoadNotices() { return {}; }

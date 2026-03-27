#ifndef ADMIN_COMPLAINT_HPP
#define ADMIN_COMPLAINT_HPP

#include "complaint.hpp"

class AdminComplaint : public Complaint {
public:
    AdminComplaint();
    AdminComplaint(int id, const string& text, int sID, const string& dateFiled);

    void UpdateStatus(const string& newStatus);
    void DeleteComplaint();
    void run();

    ~AdminComplaint();
};

#endif
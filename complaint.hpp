#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

#include <iostream>
#include <string>

using namespace std;

class Complaint {
private:
    int complaintID;
    string complaintText;
    string status; // Pending, Reviewed, Resolved

public:
    Complaint();
    Complaint(int id, const string& text);

    // Getters
    int GetComplaintID() const;
    string GetComplaintText() const;
    string GetStatus() const;
    
    // Setters
    void SetComplaintID(int id);
    void SetComplaintText(const string& text);
    void SetStatus(const string& newStatus);
    
    ~Complaint();
};

#endif

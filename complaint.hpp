#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

#include <string>

using namespace std;

class Complaint {
private:
    int complaintID;
    string complaintText;

public:
    Complaint();
    Complaint(int id, const string& text);

    void SetComplaint(const string& text);
    void UpdateComplaint(const string& newText);
    void UpdateStatus(const string& newStatus);
    
    ~Complaint();
};

#endif

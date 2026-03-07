#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

#include <string>

using namespace std;

class Complaint {
private:
    int complaintID;
    string complaintText;
    int studentID;
    string date;

public:
    Complaint();
    Complaint(int id, const string& text, int sID, const string& dateFiled);

    int GetComplaintID() const;
    string GetComplaintText() const;
    int GetStudentID() const;
    string GetDate() const;

    void SetComplaint(const string& text);
    void UpdateComplaint(const string& newText);
    void UpdateStatus(const string& newStatus);
    
    ~Complaint();
};

#endif

#include "Manager.hpp"
#include "database_handler.hpp"
#include <iostream>

using namespace std;

Manager::Manager() : Admin() {}

Manager::Manager(int id, const string& name, const string& privileges, const string& post, int accessLevel)
    : Admin(id, name, privileges, post, accessLevel) {}

void Manager::updateNotice(int id, const string& title, const string& text) {
    DatabaseHandler::UpdateNotice(id, title, text);
}

void Manager::updateComplaintStatus(Complaint& complaint, const string& status) {
    complaint.UpdateStatus(status);
}

void Manager::viewResidents() const {
    cout << "Manager viewing residents..." << endl;
}

string Manager::role() const {
    return "Manager";
}

Manager::~Manager() {}

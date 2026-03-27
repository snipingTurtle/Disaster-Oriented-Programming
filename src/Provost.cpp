#include "Provost.hpp"
#include <iostream>
#include <stdexcept>
#include "AssistantToProvost.hpp"
#include "complaint.hpp"
#include "database_handler.hpp"
#include <fstream>
#include <string>

using namespace std;

int Provost::provostCount = 0;
Provost::Provost(){}

Provost::Provost(int id,const string &name, int appointmentYear)
    : Admin(id, name, "Admin", "Provost", 10), appointmentYear(appointmentYear)
{
    if(provostCount >= 1)
    {
        throw runtime_error("Only ONE Provost is allowed in the system.");
    }
    provostCount++;
}

int Provost::getAppointmentYear() const
{
    return appointmentYear;
}

void Provost::assignShift(AssistantToProvost &assistant, const string &shift)
{
    assistant.setShift(shift);

    cout<<"Provost assigned shift '"<<shift<<"' to "<< assistant.role() << endl;
}


void Provost::updateComplaintStatus(Complaint &complaint, const string &status)
{
    complaint.UpdateStatus(status);
    DatabaseHandler::UpdateComplaintStatus(complaint.GetComplaintID(), status);

    cout << "Provost updated complaint ID "<< complaint.GetComplaintID()<< " to status: " << status << endl;
}


void Provost::viewResidents() const // Not implemented yet
{
    cout<< "Provost is viewing all residents."<<endl;
}

string Provost::role() const
{
    return "Provost";
}

void Provost::updateNotice(int id, const string& title, const string& text) {
    cout << "Notice has been updated\n";                                                       
}


Provost::~Provost()
{
    provostCount--;
}

void approve_pending() {
    string pending_file = "database/pending.csv";
    string data_file = "database/data.csv";

    ifstream pending(pending_file);
    if (!pending.is_open()) {
        cout << "Failed to open pending.csv!" << endl;
        return;
    }

    ofstream data(data_file, ios::app);
    if (!data.is_open()) {
        cout << "Failed to open data.csv!" << endl;
        pending.close();
        return;
    }

    string line;
    while(getline(pending, line)) {
        if(line.empty()) continue;  // skip empty lines
        data << line << "\n";       // append to data.csv
    }

    pending.close();
    data.close();

    ofstream clear_pending(pending_file, ios::trunc);
    clear_pending.close();

    cout << "All pending users have been approved and added to data.csv!" << endl;
}


void Provost::run(){
    while(1){
        cout << "\nProvost Panel\n";
        cout << "1: View Complaints\n";
        cout << "2: Approve Users\n";
        cout << "3: Logout\n";

        int c;
        cin >> c;

        if(c == 3) {
            cout << "Logging out from Provost Level\n";
            break;
        }
        else if(c == 2){
            cout << "did something\n";
            approve_pending();
        }
    }
}
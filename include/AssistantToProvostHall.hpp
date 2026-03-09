#ifndef ASSISTANT_TO_PROVOST_HALL_H
#define ASSISTANT_TO_PROVOST_HALL_H

#include "AssistantToProvost.h"
#include <iostream>

using namespace std;

class AssistantToProvostHall : public AssistantToProvost
{
public:
    AssistantToProvostHall(int id, const string &name, const string &shift)
        : AssistantToProvost(id, name, "Hall", shift)
    {
    }

    string role() const override
    {
        return "Assistant To Provost (Hall)";
    }

    void processRoomApplication(int studentId, int requestedRoom) const
    {
        cout<< "Processed room application for student "<<studentId<< " for room " << requestedRoom << endl;
    }

    void prepareHallReport() const
    {
        cout<<"Prepared hall activity report." << endl;
    }

    void forwardHallComplaint(int complaintId) const
    {
        cout<<"Forwarded hall complaint ID "<<complaintId<< endl;
    }
};

#endif
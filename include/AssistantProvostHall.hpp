#ifndef ASSISTANT_PROVOST_HALL_HPP
#define ASSISTANT_PROVOST_HALL_HPP
#include "AssistantProvost.hpp"

class AssistantProvostHall : public AssistantProvost
{
public:
    AssistantProvostHall(int id, const string &name)
        : AssistantProvost(id,name, "Hall") {}

    string role() const override
    {
        return "Assistant Provost (Hall)";
    }

    void allocateRoom(int studentId, int roomNo)
    {
        cout<<"Assistant Provost (Hall) allocated room "<<roomNo<<" to student ID "<< studentId << endl;
    }

    void issueWarning(int studentId) const
    {
        cout<<"Assistant Provost (Hall) issued warning to student ID "<< studentId << endl;
    }

    void reviewDisciplinaryCase(int complaintId) const
    {
        cout<<"Assistant Provost (Hall) is reviewing disciplinary complaint ID "<< complaintId<<endl;
    }
};


#endif
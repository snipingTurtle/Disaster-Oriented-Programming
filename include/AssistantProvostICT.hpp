#ifndef ASSISTANT_PROVOST_ICT_HPP
#define ASSISTANT_PROVOST_ICT_HPP
#include "AssistantProvost.hpp"

class AssistantProvostICT : public AssistantProvost
{
public:
    AssistantProvostICT(int id, const string &name)
        : AssistantProvost(id,name,"ICT") {}

    string role() const override
    {
        return "Assistant Provost (ICT)";
    }

    void scheduleMaintenance(const string &systemName) const
    {
        cout<<"Assistant Provost (ICT) scheduled maintenance for "<<systemName<<endl;
    }

    void resetUserAccess(int userId)
    {
        cout<<"Assistant Provost (ICT) reset access for user ID "<<userId<<endl;
    }

    void reviewSystemIssue(int complaintId) const
    {
        cout<<"Assistant Provost (ICT) is reviewing system complaint ID "<<complaintId << endl;
    }
};


#endif
#ifndef ASSISTANT_PROVOST_PD_HPP
#define ASSISTANT_PROVOST_PD_HPP
#include "AssistantProvost.hpp"

class AssistantProvostPD : public AssistantProvost
{
public:
    AssistantProvostPD(int id, const string &name)
        : AssistantProvost(id,name,"P&D") {}

    string role() const override
    {
        return "Assistant Provost (P&D)";
    }

    void approveRepairWork(const string &issue) const{
        cout<<"Assistant Provost (P&D) approved repair work for: "<<issue<<endl;
    }

    void scheduleRenovation(const string &location)
    {
        cout<< "Assistant Provost (P&D) scheduled renovation at "<< location << endl;
    }

    void inspectInfrastructure() const
    {
        cout << "Assistant Provost (P&D) is inspecting infrastructure." <<endl;
    }
};


#endif
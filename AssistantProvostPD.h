#ifndef ASSISTANT_PROVOST_PD_H
#define ASSISTANT_PROVOST_PD_H
#include "AssistantProvost.h"

class AssistantProvostPD : public AssistantProvost
{
public:
    AssistantProvostPD(int id, const string &name)
        : AssistantProvost(id,name,"P&D") {}

    string role() const override
    {
        return "Assistant Provost (P&D)";
    }
};


#endif
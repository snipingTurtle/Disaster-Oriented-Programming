#ifndef ASSISTANT_PROVOST_ICT_H
#define ASSISTANT_PROVOST_ICT_H
#include "AssistantProvost.h"

class AssistantProvostICT : public AssistantProvost
{
public:
    AssistantProvostICT(int id, const string &name)
        : AssistantProvost(id,name,"ICT") {}

    string role() const override
    {
        return "Assistant Provost (ICT)";
    }
};


#endif
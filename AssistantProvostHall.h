#ifndef ASSISTANT_PROVOST_HALL_H
#define ASSISTANT_PROVOST_HALL_H
#include "AssistantProvost.h"

class AssistantProvostHall : public AssistantProvost
{
public:
    AssistantProvostHall(int id, const string &name)
        : AssistantProvost(id,name, "Hall") {}

    string role() const override
    {
        return "Assistant Provost (Hall)";
    }
};


#endif
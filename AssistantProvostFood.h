#ifndef ASSISTANT_PROVOST_FOOD_H
#define ASSISTANT_PROVOST_FOOD_H
#include "AssistantProvost.h"

class AssistantProvostFood : public AssistantProvost
{
public:
    AssistantProvostFood(int id, const string &name)
        : AssistantProvost(id,name,"Food") {}

    string role() const override
    {
        return "Assistant Provost (Food)";
    }
};


#endif
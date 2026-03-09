#ifndef ASSISTANT_PROVOST_FOOD_HPP
#define ASSISTANT_PROVOST_FOOD_HPP


#include <iostream>
#include <string>
#include "AssistantProvost.hpp"
using namespace std;

class AssistantProvostFood : public AssistantProvost
{
public:
    AssistantProvostFood(int id, const string &name) : AssistantProvost(id, name, "Food") {}

    string role() const override
    {
        return "Assistant Provost (Food)";
    }

    void inspectFoodQuality() const
    {
        cout<<"Assistant Provost (Food) is inspecting food quality."<<endl;
    }

    void approveMealChange(const string &mealName)
    {
        cout<<"Assistant Provost (Food) approved meal change: "<<mealName<<endl;
    }

    void reviewCafeteriaIssue(int complaintId) const
    {
        cout<<"Assistant Provost (Food) is reviewing cafeteria complaint ID "<<complaintId<<endl;
    }
};

#endif
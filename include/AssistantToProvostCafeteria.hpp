#ifndef ASSISTANT_TO_PROVOST_CAFETERIA_HPP
#define ASSISTANT_TO_PROVOST_CAFETERIA_HPP

#include "AssistantToProvost.hpp"
#include <iostream>

using namespace std;

class AssistantToProvostCafeteria : public AssistantToProvost
{
public:
    AssistantToProvostCafeteria(int id, const string &name, const string &shift)
        : AssistantToProvost(id, name, "Cafeteria", shift)
    {}

    string role() const override
    {
        return "Assistant To Provost (Cafeteria)";
    }

    void updateMealList(const string &mealName) const
    {
        cout<<"Updated meal list with "<<mealName<<endl;
    }

    void logSupplyIssue(const string &itemName) const
    {
        cout <<"Logged supply issue for "<<itemName<< endl;
    }

    void forwardCafeteriaComplaint(int complaintId) const
    {
        cout<<"Forwarded cafeteria complaint ID "<<complaintId<<endl;
    }
};

#endif
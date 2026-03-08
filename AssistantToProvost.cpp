#include <iostream>
#include <stdexcept>
#include "AssistantToProvost.h"


using namespace std;

AssistantToProvost::AssistantToProvost(int id,
                                       const string &name,
                                       const string &responsibility,
                                       const string &shift)
    : Admin(id, name, "Admin", "Assistant To Provost", 5),
      responsibility(responsibility),
      shift(shift){}

string AssistantToProvost::getResponsibility() const
{
    return responsibility;
}

string AssistantToProvost::getShift() const
{
    return shift;
}

void AssistantToProvost::setShift(const string &shift)
{
    this->shift = shift;
}

void AssistantToProvost::updateComplaintStatus(int complaintId,
                                               const string &category,
                                               const string &status)
{
    if(category != responsibility)
    {
        throw runtime_error("Unauthorized: This Assistant To Provost cannot handle " + category + " complaints.");
    }

    cout<< "Assistant To Provost (" << responsibility<< ") updated complaint " << complaintId<<" to "<< status << endl;
}

void AssistantToProvost::viewResidents() const
{
    cout<<"Assistant To Provost responsible for "<< responsibility<< " is viewing relevant residents." << endl;
}

AssistantToProvost::~AssistantToProvost(){}
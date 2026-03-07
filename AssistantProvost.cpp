#include "AssistantProvost.h"
#include<iostream>

using namespace std;

AssistantProvost::AssistantProvost(int id,
                                   const string &name,
                                   const string &responsibility)
    : Admin(id, name,"Admin", "Assistant Provost",7),
      responsibility(responsibility) {}

void AssistantProvost::updateComplaintStatus(int complaintId, const string &status)
{
    cout <<"Assistant Provost ("<<responsibility << ") updated complaint "<< complaintId <<" to "<<status<<endl;
}

void AssistantProvost::viewResidents() const  // Not implemented
{
    cout<< "Assistant Provost responsible for "<< responsibility<<" is viewing relevant residents."<< endl;
}

AssistantProvost::~AssistantProvost() {}
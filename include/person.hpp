#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>
using namespace std;
class Person{
    protected:
        std::string name;
        int phone_number;
        std::string blood_group;
        int emergency_contact;
    public:
        Person(){

        }
        Person(std::string name, int phoneNumber, std::string bloodGroup, int emergencyContact){
            this->name = name;
            this->phone_number = phoneNumber;
            this->blood_group = bloodGroup;
            this->emergency_contact = emergencyContact;
        }
        // Setter Declarations (Mutators)
        void setName(std::string n);
        void setPhoneNumber(int p);
        void setBloodGroup(std::string b);
        void setEmergencyContact(int e);
        
        // Getter Declarations (Accessors)
        std::string getName() const;
        int getPhoneNumber() const;
        std::string getBloodGroup() const;
        int getEmergencyContact() const;
        virtual void displayDetails() const;
};
// --- Others ---
//NOTE: I had to write the displayDetails() function in this file because defining it inside the person.cpp file causes error when i run the main.cpp file as person.cpp is NOT included in the main.cpp file

#endif
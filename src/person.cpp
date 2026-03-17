#include "../include/person.hpp"
#include <iostream>
using namespace std;

// --- SETTERS ---
void Person::setName(std::string n) {
    name = n;
}

void Person::setPhoneNumber(int p) {
    phone_number = p;
}

void Person::setBloodGroup(std::string b) {
    blood_group = b;
}

void Person::setEmergencyContact(int e) {
    emergency_contact = e;
}

// --- GETTERS ---
std::string Person::getName() const {
    return name;
}

int Person::getPhoneNumber() const {
    return phone_number;
}

std::string Person::getBloodGroup() const {
    return blood_group;
}

int Person::getEmergencyContact() const {
    return emergency_contact;
}
void Person::displayDetails() const{
    std::cout << name << " " << phone_number << " " << blood_group << " " << emergency_contact << '\n';
}
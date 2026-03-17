#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../include/student_database.hpp"
#define nl '\n'
using namespace std;
unordered_map<string, student> studentDatabase::get_sd(){
    return studentDatabase;
}
void studentDatabase::loadStudentsFromFile(){
    ifstream file(rosterFile);
    string line, id, name, email, phoneNumber, emergencyContact, roomNumber, bloodGroup, hall, password;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phoneNumber, ',');
            getline(ss, emergencyContact, ',');
            getline(ss, roomNumber, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, hall, ',');
            getline(ss, password, ',');
            
            studentDatabase[id].setId(stoi(id));
            studentDatabase[id].setName(name);
            studentDatabase[id].setEmail(email);
            studentDatabase[id].setPhoneNumber(stoi(phoneNumber));
            studentDatabase[id].setEmergencyContact(stoi(emergencyContact));
            studentDatabase[id].setRoomNumber(stoi(roomNumber));
            studentDatabase[id].setBloodGroup(bloodGroup);
            studentDatabase[id].setHall(hall);
            studentDatabase[id].setPassword(password);
        }
        file.close();
    }
}
bool studentDatabase::isExistingStudent(const string& loginID) {
    if (studentDatabase.find(loginID) != studentDatabase.end()) {
        return true;
    }
    return false;
}
void studentDatabase::registerNewStudent(const std::string& password){
    int id, roomNumber, unreadMessages, phoneNumber, emergencyContact;
    string hall, name, email, bloodGroup;
    cout << "Enter your student id: ";
    cin >> id;
    //Need to get room number and hall from manager or provost, assigning a random one just for now
    roomNumber = 129;
    hall = "South";
    unreadMessages = 0;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your blood group: ";
    cin >> bloodGroup;
    cout << "Enter your phone Number: ";
    cin >> phoneNumber;
    cout << "Enter your Emergency Phone Number: ";
    cin >> emergencyContact;
    ofstream f("../data.csv", ios::app);
    f << id << "," << name << "," << email << "," << phoneNumber << "," << emergencyContact << "," << roomNumber
    << "," << bloodGroup << "," << hall << "," << password << "\n";
    f.close();
    student newStudent(id, name, email, phoneNumber, emergencyContact, roomNumber, bloodGroup, hall, password);
    studentDatabase[to_string(id)] = newStudent;
}
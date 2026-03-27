#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../include/faculty_database.hpp"
#define nl '\n'
using namespace std;
unordered_map<string, faculty> facultyDatabase::get_sd(){
    return facultyMap;
}
void facultyDatabase::loadFacultyFromFile(){
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
            
            facultyMap[id].setId(stoi(id));
            facultyMap[id].setName(name);
            facultyMap[id].setEmail(email);
            facultyMap[id].setPhoneNumber(stoi(phoneNumber));
            facultyMap[id].setEmergencyContact(stoi(emergencyContact));
            facultyMap[id].setRoomNumber(stoi(roomNumber));
            facultyMap[id].setBloodGroup(bloodGroup);
            facultyMap[id].setHall(hall);
            facultyMap[id].setPassword(password);
        }
        file.close();
    }
}
bool facultyDatabase::isExistingFaculty(const string& loginID) {
    if (facultyMap.find(loginID) != facultyMap.end()) {
        return true;
    }
    return false;
}
void facultyDatabase::registerNewFaculty(const std::string& password){
    int id, roomNumber, unreadMessages, phoneNumber, emergencyContact;
    string hall, name, email, bloodGroup;
    cout << "Enter your faculty id: ";
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
    ofstream f("../database/faculty.csv", ios::app);
    f << id << "," << name << "," << email << "," << phoneNumber << "," << emergencyContact << "," << roomNumber
    << "," << bloodGroup << "," << hall << "," << password << "\n";
    f.close();
    faculty newFaculty(id, name, email, phoneNumber, emergencyContact, roomNumber, bloodGroup, hall, password);
    facultyMap[to_string(id)] = newFaculty;
}





// facultyDatabase ff;
//         ff.loadFacultyFromFile();
//         for (auto i : ff.get_sd()) 
//             cout << i.first << ": " << i.second.getName()
//             << endl;
//         if(ff.isExistingFaculty("117")) cout << "Faculty it is" << "\n";
//         else cout << "No" << "\n";
//         if(ff.isExistingFaculty("189")) cout << "Faculty it is" << "\n";
//         else cout << "No for 189" << "\n";

//         ff.registerNewFaculty("hallershobaigay");

//         for (auto i : ff.get_sd()) 
//             cout << i.first << ": " << i.second.getName()
//             << endl;
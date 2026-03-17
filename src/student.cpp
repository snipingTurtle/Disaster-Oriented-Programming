#include <iostream>
#include <fstream>
#include <string>
#include "../include/student.hpp"
#define nl '\n'
using namespace std;

// ================== GETTER IMPLEMENTATIONS ==================

int student::getId() const { 
    return id; 
}

int student::getRoomNumber() const { 
    return roomNumber; 
}

string student::getHall() const { 
    return hall; 
}

string student::getPassword() const { 
    return password; 
}

string student::getEmail() const { 
    return email; 
}

int student::getUnreadMessages() const { 
    return unreadMessages; 
}

// ================== SETTER IMPLEMENTATIONS ==================

void student::setId(int newId) { 
    id = newId; 
}

void student::setRoomNumber(int newRoomNumber) { 
    roomNumber = newRoomNumber; 
}

void student::setHall(const string& newHall) { 
    hall = newHall; 
}

void student::setPassword(const string& newPassword) { 
    password = newPassword; 
}

void student::setEmail(const string& newEmail) { 
    email = newEmail; 
}

void student::setUnreadMessages(int newUnreadMessages) { 
    unreadMessages = newUnreadMessages; 
}
void student::getCountOfUnreadMessages(){
    string fileName = "../Messages/" + to_string(id) + "Unread.txt";
    ifstream inFile(fileName);
    string line;
    while (getline(inFile, line)) {
        unreadMessages++;
    }
    cout << unreadMessages << "messages" << "\n";
}
void student::readMessages(){
    string fileName = "../Messages/" + to_string(id) + "Unread.txt";
    ifstream inFile(fileName);
    string fileName2 = "../Messages/" + to_string(id) + "Read.txt";
    ofstream outFile;
    outFile.open(fileName2, ios::app);
    string line;
    while (getline(inFile, line)) {
        cout << line << "\n";
        outFile << line << "\n";
    }
    inFile.close();
    outFile.close();
    outFile.open(fileName, ios::trunc);
    if (outFile.is_open()) {
        cout << "File '" << fileName << "' has been successfully cleared.\n";
        outFile.close();
    } else {
        cerr << "Error: Could not open the file to clear it.\n";
    }
}
void student::writeMessage(){
    int destination;
    cout << "Enter the id of recipient: ";
    cin >> destination;
    cin.ignore();
    string fileName = "../Messages/" + to_string(destination) + "Unread.txt";
    ofstream outFile;
    outFile.open(fileName, ios::app);
    string message;
    cout << "Enter your message, press ~ and enter when done: " << "\n";
    getline(cin, message, '~');
    outFile << message << "\n";
    cout << "Message Sent Successfully!" << "\n";
    outFile.close();
}
void student::readReadMessagesFile(){
    string fileName = "../Messages/" + to_string(id) + "Read.txt";
    ifstream inFile(fileName);
    string line;
    while (getline(inFile, line)) {
        cout << line << "\n";
    }
    inFile.close();
}
void Student(){
    cout << "Student data" << nl;
    //student s1(129, "Zahin", 159154, "O+", 39629, 123, "South Hall");
    //s1.displayDetails();
}
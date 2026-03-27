#include <iostream>
#include <fstream>
#include <string>
#include "../include/faculty.hpp"
#define nl '\n'
using namespace std;

// ================== GETTER IMPLEMENTATIONS ==================

int faculty::getId() const { 
    return id; 
}

int faculty::getRoomNumber() const { 
    return roomNumber; 
}

string faculty::getHall() const { 
    return hall; 
}

string faculty::getPassword() const { 
    return password; 
}

string faculty::getEmail() const { 
    return email; 
}

int faculty::getUnreadMessages() const { 
    return unreadMessages; 
}

// ================== SETTER IMPLEMENTATIONS ==================

void faculty::setId(int newId) { 
    id = newId; 
}

void faculty::setRoomNumber(int newRoomNumber) { 
    roomNumber = newRoomNumber; 
}

void faculty::setHall(const string& newHall) { 
    hall = newHall; 
}

void faculty::setPassword(const string& newPassword) { 
    password = newPassword; 
}

void faculty::setEmail(const string& newEmail) { 
    email = newEmail; 
}

void faculty::setUnreadMessages(int newUnreadMessages) { 
    unreadMessages = newUnreadMessages; 
}
void faculty::getCountOfUnreadMessages(){
    string fileName = "../Messages/" + to_string(id) + "Unread.txt";
    ifstream inFile(fileName);
    string line;
    while (getline(inFile, line)) {
        unreadMessages++;
    }
    cout << unreadMessages << "messages" << "\n";
}
void faculty::readMessages(){
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
void faculty::writeMessage(){
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
void faculty::readReadMessagesFile(){
    string fileName = "../Messages/" + to_string(id) + "Read.txt";
    ifstream inFile(fileName);
    string line;
    while (getline(inFile, line)) {
        cout << line << "\n";
    }
    inFile.close();
}
void Faculty(){
    cout << "Faculty data" << nl;
    //faculty f1(129, "Zahin", 159154, "O+", 39629, 123, "South Hall");
    //f1.displayDetails();
}

void faculty::run(){
    while(1){
        cout << "\nFaculty Panel\n";
        cout << "1: View Notices\n";
        cout << "2: Give General Announcement\n";
        cout << "3: Send Message\n";
        cout << "4: Read Messages\n";
        cout << "5: Set Complaint\n";
        cout << "6: Exit\n";

        int c;
        cin >> c;

        if(c == 3) {
            cout << "Logging out from Faculty Level\n";
            break;
        }
}
}
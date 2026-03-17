#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "person.hpp"
using namespace std;
class student : public Person{
    private:
        int id;
        int roomNumber;
        string hall;
        string password;
        string email;
        int unreadMessages;
    public:
        student(){
            unreadMessages = 0;
        }
        //int roomNumber, std::string name, string password, string email, int phoneNumber, std::string bloodGroup, int emergencyContact, int id, string hall
        student(int id, string name, string email, int phoneNumber, int emergencyContact, int roomNumber, string bloodGroup, string hall, string password) : Person(name, phoneNumber, bloodGroup, emergencyContact){
            this->roomNumber = roomNumber;
            this->id = id;
            this->hall = hall;
            this->email = email;
            this->password = password;
            unreadMessages = 0;
        }
        // ================== GETTER DECLARATIONS ==================
        int getId() const;
        int getRoomNumber() const;
        string getHall() const;
        string getPassword() const;
        string getEmail() const;
        int getUnreadMessages() const;

        // ================== SETTER DECLARATIONS ==================
        void setId(int newId);
        void setRoomNumber(int newRoomNumber);
        void setHall(const string& newHall);
        void setPassword(const string& newPassword);
        void setEmail(const string& newEmail);
        void setUnreadMessages(int newUnreadMessages);


        void getCountOfUnreadMessages();
        void readMessages();
        void writeMessage();
        void readReadMessagesFile();

        //bool checkFirstTimeLogin();
        //void firstTimeLogin();
};
#endif
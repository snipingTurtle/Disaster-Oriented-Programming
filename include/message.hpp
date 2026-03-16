#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include<chrono>

using namespace std;

class Message
{
private:
    static int idGen;
    const int message_id;
    int sender_id;
    int reciever_id;
    string content;
    chrono::system_clock::time_point timestamp;
    bool unread;

public:
    Message();
    Message(const int &sender, const int &reciever, const string &s);

    // Setter Functions
    void setSender(const int &sender);
    void setReciever(const int &reciever);
    void setContent(const string &s);

    int getSender() const;
    int getReciever() const;
    string getContent() const;
    int getMessageID() const;
    chrono::system_clock::time_point getTime() const;
    bool getUnread() const;

    ~Message();
};

#endif
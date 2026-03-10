#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include<chrono>

using namespace std;

class Message
{
private:
    static int message_id;
    int sender_id;
    int reciever_id;
    string content;
    chrono::system_clock::time_point timestamp;

public:
    Message();
    Message(const int &sender, const int &reciever, const string &s);

    // Setter Functions
    void setSender(const int &sender);
    void setReciever(const int &reciever);
    void setContent(const string &s);

    virtual void setMessage() = 0;

    int getSender() const;
    int getReciever() const;
    int getContent() const;

    void DeleteMessage();
    void SaveMessage();

    ~Message();
};

#endif
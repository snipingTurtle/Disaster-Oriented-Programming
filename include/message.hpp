#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

using namespace std;

class Message
{
private:
    static int message_id;
    int sender_id;
    int reciever_id;
    string content;
    string timestamp;

public:
    Message();
    Message(const int &sender, const int &reciever, const string &s, const string &time);

    void sendMessage(const int &sender, const int &reciever, const string &s, const string &time);
    void storeMessage();
    void getMessage();

    ~Message();
};

#endif
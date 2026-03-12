#include "message.hpp"
#include <iostream>

using namespace std;

int Message::idGen = 0;

Message::Message() :
{
}

Message::Message(const int &sender, const int &reciever, const string &s) : message_id(idGen++) sender_id(sender), reciever_id(reciever), timestamp(chrono::system_clock::now()), read(false)
{
    setContent(s);
}

void Message::setSender(const int &sender)
{
    sender_id = sender;
}

void Message::setReciever(const int &reciever)
{
    reciever_id = reciever;
}

void Message::setContent(const string &s)
{
    if (s.size() > 1000)
    {
        throw runtime_error("Size of the Message cannot exceed 1000 characters including space.");
    }
    content = s;
}

int Message::getSender() const
{
    return sender_id;
}

int Message::getReciever() const
{
    return reciever_id;
}

string Message::getContent() const
{
    return content;
}
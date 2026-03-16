#include "message.hpp"
#include <iostream>

using namespace std;

int Message::idGen = 1;

Message::Message() : message_id(idGen++), sender_id(0), reciever_id(0), content("NULL"), timestamp(chrono::system_clock::now()), unread(true)
{
}

Message::Message(const int &sender, const int &reciever, const string &s) : message_id(idGen++), sender_id(sender), reciever_id(reciever), timestamp(chrono::system_clock::now()), unread(true)
{
    setContent(s);
}

Message::Message(const int &id, const int &sender, const int &reciever, const string &s, chrono::system_clock::time_point time, bool status) : message_id(id), sender_id(sender), reciever_id(reciever), timestamp(time), unread(status)
{
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

int Message::getMessageID() const
{
    return message_id;
}

chrono::system_clock::time_point Message::getTime() const
{
    return timestamp;
}

bool Message::getUnread() const
{
    return unread;
}

void Message::SaveMessage()
{
    ofstream outFile("messages.csv", ios::app);
    if (outFile.is_open())
    {
        outFile << getMessageID() << ","
                << getSender() << ","
                << getReciever() << ","
                << getContent() << ","
                << getTime() << ",";
        << getUnread() << endl;
        outFile.close();
    }
    else
    {
        cerr << "Error: Could not open messages.csv for writing." << endl;
    }
}

Message::~Message() {}
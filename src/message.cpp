#include "message.hpp"
#include "database_handler.hpp"
#include <iostream>
#include <chrono>
#include <ctime>

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

void Message::Send() const
{
    DatabaseHandler::SaveMessage(*this);
}

void Message::MarkAsRead()
{
    unread = false;
}

void Message::operator=(const string &s)
{
    setContent(s);
}

string operator+(const string &s, const Message &message)
{
    return s + message.getContent();
}

Message::operator string() const
{
    return getContent();
}

ostream &operator<<(ostream &o, const Message &message)
{
    time_t t = chrono::system_clock::to_time_t(message.getTime());

    string timeStr = ctime(&t);
    timeStr.pop_back(); 

    o << "[" << timeStr << "] "
      << message.getSender() << " -> "
      << message.getReciever() << ": "
      << message.getContent() << endl;

    // [Sun Mar 16 16:12:45 2026] 1 -> 2: Hello!

    return o;
}

string readCSVField(stringstream &ss)
{
    string field;

    if (ss.peek() == '"')
    {
        ss.get(); // remove opening quote

        char c;
        while (ss.get(c))
        {
            if (c == '"')
            {
                if (ss.peek() == '"') // escaped quote
                {
                    field += '"';
                    ss.get();
                }
                else
                {
                    break; // end quote
                }
            }
            else
            {
                field += c;
            }
        }

        if (ss.peek() == ',')
            ss.get();
    }
    else
    {
        getline(ss, field, ',');
    }

    return field;
}

istream& operator>>(istream& in, Message& message)
{
    string line;
    if (!getline(in, line))
        return in; // EOF

    stringstream ss(line);
    
    string id, sender, receiver, time, unread;

    getline(ss, id, ',');
    getline(ss, sender, ',');
    getline(ss, receiver, ',');

    string content = readCSVField(ss);

    getline(ss, time, ',');
    getline(ss, unread);

    int msgID = stoi(id);
    int s = stoi(sender);
    int r = stoi(receiver);
    time_t t = stoll(time);

    chrono::system_clock::time_point tp =
        chrono::system_clock::from_time_t(t);

    bool status = (unread == "1" || unread == "true");

    message = Message(msgID, s, r, content, tp, status);

    return in;
}

Message::~Message() {}
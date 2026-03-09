#include "Admin.h"
#include<fstream>
#include<sstream>
#include<vector>

// constructor
Admin::Admin(int id,
             const string &name,
             const string &privileges,
             const string &post,
             int accessLevel) : User(id, name, privileges), post(post), accessLevel(accessLevel){}

// getter functions
string Admin::getPost() const
{
    return post;
}

string Admin::getPhoneNumber() const
{
    return phoneNumber;
}

int Admin::getAccessLevel() const
{
    return accessLevel;
}

string Admin::getEmail() const
{
    return email;
}

string Admin::getOfficeRoom() const
{
    return officeRoom;
}


// setter functions
void Admin::setPhoneNumber(const string &phone)
{
    phoneNumber = phone;
}

void Admin::setAccessLevel(int level)
{
    accessLevel = level;
}

void Admin::setEmail(const string &email)
{
    this->email = email;
}

void Admin::setOfficeRoom(const string &room)
{
    officeRoom = room;
}


static vector<string> splitCSVLine(const string &line)
{
    vector<string> fields;
    string field;
    stringstream ss(line);

    while (getline(ss, field, ','))
    {
        fields.push_back(field);
    }

    return fields;
}

static string joinCSVLine(const vector<string> &fields)
{
    string line;

    for (size_t i = 0; i < fields.size(); i++)
    {
        line += fields[i];
        if (i + 1 < fields.size())
        {
            line += ",";
        }
    }

    return line;
}

static bool isNoticeHeader(const vector<string> &fields)
{
    return !fields.empty() && fields[0] == "noticeId";
}

void Admin::postNotice(const string &text)
{
    const string fileName = "notices.csv";
    ifstream inFile(fileName);
    string line;
    int lastId = 0;
    bool fileExists = inFile.is_open();
    bool hasHeader = false;

    if (fileExists)
    {
        while (getline(inFile, line))
        {
            if (line.empty())
                continue;

            vector<string> fields = splitCSVLine(line);

            if (isNoticeHeader(fields))
            {
                hasHeader = true;
                continue;
            }

            if (!fields.empty())
            {
                try
                {
                    int id = stoi(fields[0]);
                    if (id > lastId)
                    {
                        lastId = id;
                    }
                }
                catch (...)
                {
                    // Ignore malformed rows to stay compatible with others
                }
            }
        }
        inFile.close();
    }

    ofstream outFile(fileName, ios::app);

    if (!outFile.is_open())
    {
        cout << "Error: Could not open notices.csv" << endl;
        return;
    }

    if (!fileExists)
    {
        outFile << "noticeId,role,name,text\n";
    }
    else if (fileExists && !hasHeader)
    {
        // Do nothing; keep compatibility with headerless existing file
    }

    outFile << (lastId + 1) << ","
            << role() << ","
            << getName() << ","
            << text << "\n";

    outFile.close();

    cout << "[" << role() << "] posted notice successfully." << endl;
}

void Admin::updateNotice(int noticeId, const string &newText)
{
    const string fileName = "notices.csv";
    ifstream inFile(fileName);

    if (!inFile.is_open())
    {
        cout << "Error: notices.csv not found." << endl;
        return;
    }

    vector<string> allLines;
    string line;
    bool found = false;

    while (getline(inFile, line))
    {
        if (line.empty())
        {
            allLines.push_back(line);
            continue;
        }

        vector<string> fields = splitCSVLine(line);

        if (isNoticeHeader(fields))
        {
            allLines.push_back(line);
            continue;
        }

        if (!fields.empty())
        {
            try
            {
                int currentId = stoi(fields[0]);

                if (currentId == noticeId)
                {
                    while (fields.size() < 4)
                    {
                        fields.push_back("");
                    }

                    fields[3] = newText;
                    line = joinCSVLine(fields);
                    found = true;
                }
            }
            catch (...)
            {
                // Ignore malformed rows and preserve them
            }
        }

        allLines.push_back(line);
    }

    inFile.close();

    if (!found)
    {
        cout << "Notice ID " << noticeId << " not found." << endl;
        return;
    }

    ofstream outFile(fileName, ios::trunc);

    if (!outFile.is_open())
    {
        cout << "Error: Could not rewrite notices.csv" << endl;
        return;
    }

    for (size_t i = 0; i < allLines.size(); i++)
    {
        outFile << allLines[i] << "\n";
    }

    outFile.close();

    cout << "[" << role() << "] updated notice ID "
         << noticeId << " successfully." << endl;
}

void Admin::viewProfile() const
{
    cout << "\n----- Admin Profile -----\n";
    cout << "Name: " << getName() << endl;
    cout << "Role: " << role() << endl;
    cout << "Post: " << post << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Email: " << email << endl;
    cout << "Office Room: " << officeRoom << endl;
    cout << "Access Level: " << accessLevel << endl;
    cout << "Privileges: " << getPriviledges() << endl;
    cout << "-------------------------\n";
}


// destructor
Admin::~Admin(){}
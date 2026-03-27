#include "Authorization.hpp"

void Authorization::sign_up(string in_name, string in_email, string pass, string role) {
    string file_name = "database/data.csv";
    ifstream f(file_name);
    if (!f.is_open()) {
            cout << "Failed to open Data.csv!" << endl;
            return;
        }

    string line;
    int flag = 0;

    while(getline(f, line)) {
        stringstream ss(line);
        string n, e, p, r;

        getline(ss, n, ',');
        getline(ss, e, ',');
        getline(ss, p, ',');
        getline(ss, r);
        if(n == in_name || e == in_email) {
            flag = 1;
            break;
        }
    }
    f.close();

    if(flag == 1) {
        cout << "Name or Email already exists\n";
    }
    else {
        cout << "Awaiting Admin approval!" << endl;
        string pending = "database/pending.csv";
        
        ofstream f(pending, ios::app);
        if (!f.is_open()) {
            cout << "Failed to open pending.csv!" << endl;
            return;
        }
        for(int i = 0; i < role.size(); i++) {
            role[i] = tolower(role[i]);
        }
        if(role == "s") role = "student";
        else if(role == "pf") role = "part time faculty";
        else if(role == "f") role = "faculty";
        else if(role == "p") role = "provost";
        else if(role == "m") role = "manager";

        f << in_name << "," << in_email << "," << pass << "," << role << "\n";
        f.close();
    }
}

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \r\n\t");
    size_t end = s.find_last_not_of(" \r\n\t");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

string Authorization::log_in(string name_or_email, string pass) {
    string file_name = "database/data.csv";
    ifstream f(file_name);
    if (!f.is_open()) {
        cout << "Failed to open data.csv!" << endl;
        return "null";
    }
    string line;
    bool flag = 1;
    string n, e, p, r;
    while(getline(f, line)) {
        stringstream ss(line);
        getline(ss, n, ',');
        getline(ss, e, ',');
        getline(ss, p, ',');
        getline(ss, r);
        r = trim(r);
        if(n == name_or_email || e == name_or_email) {
            if(p == pass) {
                flag = 0;
            }
            break;
        }
    }
    f.close();

    if(flag == 1) return "null";
    else return r;
}
#ifndef AUTHORIZATION_HPP
#define AUTHORIZATION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Authorization {
private:
    string name;
    string email;
    string password;

public:
    void sign_up(string in_name, string in_email, string pass, string role);
    string log_in(string name_or_email, string pass);
};

#endif
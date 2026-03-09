#include <iostream>
#include <fstream>
#include <sstream>

#include "all.hpp"

using namespace std;

class Authorization{
    private:
        string name;
        string email;
        string password;
    public:
        void sign_up(string in_name, string in_email, string pass, string role){
            string file_name = "../database/data.csv";
            ifstream f(file_name);

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
            if(flag == 1) {
                cout << "Name or Email already exists\n";
            }
            else {
                string pending = "../database/pending.csv";
                ofstream f(pending, ios::app);
                for(int i = 0; i < role.size(); i++){
                    role[i] = tolower(role[i]);
                }
                if(role == "s") role = "student";
                else if(role == "pf") role = "part time faculty";
                if(role == "f") role = "faculty";
                if(role == "p") role = "provost";
                if(role == "m") role = "manager";

                f << in_name << "," << in_email << "," << pass << "," << role << "\n";
                f.close();
            }
        }
        string log_in(string name_or_email, string pass){
            string file_name = "../database/data.csv";
            ifstream f(file_name);

            string line;
            bool flag = 1;
            string n, e, p, r;
            while(getline(f, line)) {
                stringstream ss(line);
                getline(ss, n, ',');
                getline(ss, e, ',');
                getline(ss, p, ',');
                getline(ss, r);

                if( (n == name_or_email) || (e == name_or_email) ) {
                    if(p == pass){
                        flag = 0;
                    }
                    break;
                }
            }

            if(flag == 1) {
                return "null";
            }
            else {
                return r;
            }
        }
};

int main(){
    string choice;
    Authorization auth;
    while(1){
        cout << "\n1: Login";
        cout << "\n2: Sign-Up";
        cout << "\n3: Exit";
        cout << "\nEnter Your Choice :: ";
        
        cin >> choice;
        if(choice.size() != 1) {
            cout << "Invalid input\n";
            continue;
        }
        else if(choice[0] == '3'){
            break;
        }
        else if(choice[0] == '1'){
            string a, b;
            cout << "Enter your User Name or Email: "; cin >> a;
            cout << "Enter your password: "; cin >> b;
            
            string r = auth.log_in(a,b);
            if(r == "null") {
                cout << "Credentials mismatch\n";
                continue;
            }
            else if(r == "student"){
                cout << "Calling student UI\n";
            }
            else if(r == "faculty"){
                cout << "Calling faculty UI\n";
            }
            else if(r == "part time faculty"){
                cout << "Calling part time faculty UI\n";
            }
            else if(r == "provost"){
                cout << "Calling provost UI\n";
            }
            else if(r=="manager"){
                cout << "Calling manager UI\n";
            }
        }
        else if(choice[0] == '2'){
            string a, b, c, d;
            cout << "Enter your name: "; cin >> a;
            cout << "Enter your email: "; cin >> b;
            cout << "Enter your password: "; cin >> c;
            cout << "S/PF/F/P/M: "; cin >> d;
            auth.sign_up(a,b,c,d);
            cout << "Awaiting Admin approval!" << endl;
        }
        else {
            cout << "Invalid input\n";
            continue;
        }
    }    
}
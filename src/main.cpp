#include <iostream>
#include<fstream>
#include<sstream>

#include "user.hpp"
#include "complaint.hpp"
#include "student.hpp"
#include "person.hpp"
#include "student_database.hpp"

using namespace std;
class Authorization{
    private:
        string name;
        string email;
        string password;
    public:
        void sign_up(string in_name, string in_email, string pass){
            string file_name = "data.csv";
            ifstream f(file_name);

            string line;
            int flag = 0;

            while(getline(f, line)) {
                stringstream ss(line);
                string n, e, p;

                getline(ss, n, ',');
                getline(ss, e, ',');
                getline(ss, p, ',');
                if(n == in_name || e == in_email) {
                    flag = 1;
                    break;
                }
            }
            if(flag == 1) {
                cout << "Name or Email already exists\n";
            }
            else {
                //Need to change here so that more info about student can be added ~ Zahin
                ofstream f(file_name, ios::app);
                f << in_name << "," << in_email << "," << pass << "\n";
                f.close();
            }
        }
        void log_in(string name_or_email, string pass){
            string file_name = "data.csv";
            ifstream f(file_name);

            // string in_name, in_email;
            // cin >> in_name >> in_email;

            string line;
            int flag = 0;

            while(getline(f, line)) {
                stringstream ss(line);
                string n, e, p;

                getline(ss, n, ',');
                getline(ss, e, ',');
                getline(ss, p, ',');
                if(n == name_or_email || n == name_or_email) {
                    if(password != pass){
                        flag = 1;
                    }
                    break;
                }
            }
            if(flag == 1) {
                cout << "Wrong Credentials\n";
            }
            else {
                cout << "Successful Login\n";
            }
        }
};

int main(){
    char choice;
    Authorization auth;
    while(1){
        cout << "\n1: Login";
        cout << "\n2: Sign-Up";
        cout << "\n3: Forgot Password";
        cout << "\n4: Exit";
        cout << "\nEnter q to quit";
        cout << "\nEnter Your Choice :: ";
        
        cin >> choice;
        if(choice == 'q' or choice == 'Q'){
            break;
        }
        else if(choice == '1'){
            string a, b;
            
            cout << "Enter your User Name or Password: "; cin >> a;
            cout << "Enter your password: "; cin >> b;
            auth.log_in(a,b);
        }
        else if(choice == '2'){
            string a, b, c;
            cout << "Enter your name: "; cin >> a;
            cout << "Enter your email: "; cin >> b;
            cout << "Enter your password: "; cin >> c;
            auth.sign_up(a,b,c);
        }
    }
    
    
}
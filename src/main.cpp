#include <iostream>
#include "all.hpp"

using namespace std;

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
                Provost p;
                cout << "Calling provost UI\n";
                p.run();
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
        }
        else {
            cout << "Invalid input\n";
            continue;
        }
    }    
}
#include <iostream>
#include "User.h"

using namespace std;

int main()
{   
    User me(1, "Labib", "none");
    me.Register();
    me.LogIn();

    cout<<"everything is properly working"<<endl;

    return 0;
}


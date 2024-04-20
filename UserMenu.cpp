#include "UserMenu.h"

#include<iostream>
#include<string>
using namespace std;
UserMenu::UserMenu()
{
    string choice;
    cout<<"1.View Current Balance\n2.View history of transactions\n3.edit Profile\n4.Send money\n5.Request money\n";
    cin>>choice;
    if(choice!="1" and choice!="2" and choice!="3" and choice!="4" and choice!="5")
    {
        cout<<"Invalid choice,enter a valid number\n";
        UserMenu();
        return;
    }
}

UserMenu::~UserMenu()
{

}
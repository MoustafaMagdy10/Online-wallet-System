#ifndef USERMENU_H
#define USERMENU_H

#pragma once
#include "Person.h"
#include<map>
class UserMenu
{
public:
    UserMenu(Person *currentUser,map<string, Person*> personStore);
    //1.View Current Balance\n2.View history of transactions\n
    //3.edit Profile\n4.Send money\n5.Request money\n6.Add Money\n7.Log out\n";
    void viewCurrrentBalance(Person *currentUser);
    void tansactionHistory(Person *currentUser);
    void UserMenu::editProfile(Person *currentUser);
    void sendMoney(Person *currentUser,map<string, Person*> personStore);
    void requestMoney(Person *currentUser,map<string, Person*> personStore);
    void addMoney(Person *currentUser);
    void logOut();

private:

};

#endif
#ifndef UserMenu_H
#define UserMenu_H

#pragma once
#include "Person.h"
#include "User.h"

// map<string, Person *> Person::personStore;
// Person *Person::currentPerson = nullptr;
// User *User::currentUser = nullptr;
#include<map>
class UserMenu
{
public:
    //UserMenu();
    UserMenu(User *currentUser,map<string, Person*> personStore);
    // 1.View Current Balance\n2.View history of transactions\n
    // 3.edit Profile\n4.Send money\n5.Request money\n6.Add Money\n7.Log out\n";
    // void viewCurrrentBalance(Person *currentPerson);
    // void tansactionHistory(Person *currentPerson);
    // void UserMenu::editProfile(Person *currentPerson);
    void sendMoney(User *currentPerson,map<string, Person*> personStore);
    void requestMoney(User *currentPerson,map<string, Person*> personStore);
    // void addMoney(Person *currentPerson);
    // void logOut();
    ~UserMenu();

private:

};

#endif
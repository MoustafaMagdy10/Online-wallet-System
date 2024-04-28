#ifndef UserMenu_H
#define UserMenu_H

#pragma once
#include "Person.h"
#include "User.h"

#include<map>
class UserMenu
{
public:
    UserMenu(User *currentUser,map<string, Person*> personStore);
    void sendMoney(User *currentPerson,map<string, Person*> personStore);
    void requestMoney(User *currentPerson,map<string, Person*> personStore);
    ~UserMenu();

private:

};

#endif
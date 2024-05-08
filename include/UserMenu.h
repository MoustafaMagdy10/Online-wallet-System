#ifndef UserMenu_H
#define UserMenu_H

#pragma once
#include "Person.h"
#include "User.h"

#include <map>
class UserMenu
{
public:
    UserMenu(const int &choice);
    void sendMoney();
    // void requestMoney(User *currentPerson,map<string, Person*> personStore);
    ~UserMenu();

private:
};

#endif
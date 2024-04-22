#ifndef USER_H
#define USER_H

#pragma once

#include<iostream>
#include "Person.h"

using namespace std;

class User : public Person
{
public:
    static User *currentUser;
    User(const string &userName ,const string &password);
    ~User();

private:
    long double balance;
};

#endif
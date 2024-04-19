#ifndef USER_H
#define USER_H

#pragma once

#include<iostream>
#include "Person.h"

using namespace std;

class User : public Person
{
public:
    User(string userName , string password);
    ~User();

private:
    long long balance;
};

#endif
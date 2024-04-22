#ifndef ADMIN_H
#define ADMIN_H

#pragma once

#include<iostream>
#include "Person.h"

using namespace std;
class Admin : public Person
{
public:
    static Admin *currentAdmin;
    Admin(string userName , string password);
    ~Admin();

private:

};

#endif
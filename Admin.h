#ifndef ADMIN_H
#define ADMIN_H

#pragma once

#include <iostream>
#include "Person.h"

using namespace std;
class Admin : public Person
{
public:
    static Admin *currentAdmin;
    Admin();
    Admin(const string &userName,const string &password);
    ~Admin();

private:
};

#endif
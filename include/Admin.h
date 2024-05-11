#ifndef ADMIN_H
#define ADMIN_H

#pragma once

#include <iostream>
#include "Person.h"
#include "User.h"
using namespace std;
class Admin : public Person
{
public:
    static Admin *currentAdmin;
    Admin();
    Admin(const string &userName,const string &password);
    void deleteUser();
    void suspendUser();
    ~Admin();
    void viewAllUsers();
    void viewAllTransactions();
    void editUserBalance();
    void addUser();
private:
};

#endif
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
    Admin(const string &userName,const uint64_t &password);
    void deleteUser();
    void suspendUser();
    void ActivateUser();
    ~Admin();
    void viewAllUsers();
    void viewAllTransactions();
    void editUserBalance();
    void addUserBalance();
    void addUser();

private:
};

#endif
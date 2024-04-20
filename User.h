#ifndef USER_H
#define USER_H

#pragma once

#include<iostream>
#include<stack>
#include "Person.h"
#include "Transaction.h"

using namespace std;

class User : public Person
{
public:
    User(string userName,string password);

   void sendMoney(string recipientUsername,double amount);
   void requestMoney(string senderUsername,double amount);

    ~User();

private:
    double balance;
    string email;
    string phoneNumber;
   // stack<Transaction>transactionHistory;
};

#endif
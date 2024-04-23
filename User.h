#ifndef USER_H
#define USER_H

#pragma once

#include<iostream>
#include<stack>
#include "Person.h"
// #include "Transaction.h"

using namespace std;

class User : public Person
{
public:

    static User *currentUser;
    
    User(const string &userName ,const string &password);
   void sendMoney(string recipientUsername,double amount);
   void requestMoney(string senderUsername,double amount);
   double getBalance();
    ~User();

private:
    long double balance;
//    stack<Transaction>transactionHistory;

    
};

#endif
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

    static User *currentUser;
    
    User(const string &userName ,const string &password);
//    void sendMoney(string recipientUsername,double amount);
//    void requestMoney(string senderUsername,double amount);
   long double getBalance();
   void setBalance(double balance);
   void setUserName(string userName);
   string getUserName();
   stack<Transaction> getTransactionHistory();
    void addTransaction(Transaction transaction);
    void viewCurrrentBalance();
    void viewTansactionHistory();
    void editProfile();
    // void sendMoney();
    // void requestMoney();
    void addMoney();
    void logOut();

    ~User();

private:
    long double balance;
    stack<Transaction>transactionHistory;
};

#endif
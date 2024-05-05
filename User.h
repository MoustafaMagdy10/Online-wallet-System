#ifndef USER_H
#define USER_H

#pragma once

#include<iostream>
#include<stack>
#include<queue>
#include "Person.h"
#include "Transaction.h"

using namespace std;

class User : public Person
{
public:

    static User *currentUser;
    
    User(const string &userName ,const string &password);
   void sendMoney(string recipientUsername,double amount);
//    void requestMoney(string senderUsername,double amount);
   long double getBalance();
   void setBalance(double balance);
//    void setUserName();
//    string getUserName();
   stack<Transaction> getTransactionHistory();
    void addTransaction(Transaction transaction);
    void viewCurrrentBalance();
    void viewTansactionHistory();
   //  void editProfile();
    void viewTansForAdmin();
    // void sendMoney();
    // void requestMoney();
    void addMoney();
    void logOut();

    ~User();

private:
   queue<string> inbox;
    long double balance;
    stack<Transaction>transactionHistory;
};

#endif
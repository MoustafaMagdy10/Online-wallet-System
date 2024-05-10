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
   void sendMoney();
   void requestMoney();
   stack<Transaction> getTransactions();
   void Notification(const string &message);
   long double getBalance();
   void setBalance(const double &balance);
   stack<Transaction> getTransactionHistory();
    void addTransaction(Transaction transaction);
    void viewTransactionHistory();
    void viewTransactionHistory(const User* user);
    void viewTansForAdmin();
   //  void addMoney();
   void ShowCredential() override;
    void ShowInbox();
    bool hasNotification();
    void setSuspended(const bool &suspended);
    bool getSuspended();
    ~User();

private:
   stack<string> inbox;
    long double balance;
    stack<Transaction>transactionHistory;
    bool suspended = false;
};

#endif
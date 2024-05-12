#ifndef USER_H
#define USER_H

#pragma once

#include <iostream>
#include <stack>
#include <queue>
#include "Person.h"
#include "Transaction.h"

using namespace std;

class User : public Person
{
public:
    static User *currentUser;

    User(const string &userName, const string &password);
    User(const string &userName, const uint64_t &password);
    void sendMoney();
    void requestMoney();
    stack<Transaction> getTransactions();
    void Notify(const string &message);
    long double getBalance();
    void setBalance(const double &balance);
    stack<Transaction> getTransactionHistory();
    void addTransaction(Transaction transaction);
    void viewTransactionHistory();
    void viewTransactionHistory(const User *user);
    void viewTansForAdmin();
    stack<string> getInbox();
    //  void addMoney();
    void ShowCredential() override;
    void ShowInbox();
    void addForInbox(const string &message);
     bool hasNotification();
    void setSuspended(const bool &suspended);
    bool getSuspended();
    ~User();

private:
    stack<string> inbox;
    long double balance;
    stack<Transaction> transactionHistory;
    bool suspended = false;
};

#endif
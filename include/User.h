#ifndef USER_H
#define USER_H

#pragma once

#include <iostream>
#include <stack>
#include <queue>
#include <iomanip>

#include "Person.h"
#include "Transaction.h"
#include "Notfication.h"
#include "Menu.h"
#include "Admin.h"
#include "Menu.h"
#include "Admin.h"

using namespace std;

class User : public Person
{
public:
    static User *currentUser;

    User(const string &userName, const string &password);
    User(const string &userName, const uint64_t &password);

    void sendMoney();
    void requestMoney();

    void addTransaction(Transaction transaction);
    void viewTransactionHistory();
    void viewTransactionHistory(const User *user);


    void ShowCredential() override;


    void ShowInbox();
    void Notify(const Notification &N);
    bool hasNotification();

    void setBalance(const double &balance);
    void setSuspended(const bool &suspended);

    stack<Transaction> getTransactions();
    stack<Transaction> getTransactionHistory();
    stack<Notification> getInbox();
    queue<string> getQuickList();
    long double getBalance();
    bool getSuspended();

    void manageQuickList(const string &name);

    ~User();

private:
    stack<Notification> inbox;
    queue<string>quickList;
    long double balance;
    stack<Transaction> transactionHistory;
    bool suspended = false;
};

#endif
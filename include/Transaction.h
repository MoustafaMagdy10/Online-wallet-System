#ifndef Transaction_H
#define Transaction_H

#pragma once
#include <string>
#include <chrono>
#include<stack>

using namespace std;
class Transaction {
public:
    Transaction();
    Transaction(string sender, string recipient, double amount, string type);
    static string get_current_time();
    void setAmount(double amount);
    void setType(string type);
    // stack<Transaction*> getAllTransactions();
    string getType();
    string getSender();
    string getRecipient();
    double getAmount();
    string getTransactionDate();
    static stack<Transaction*>transactionStore;
private:
    string sender;
    string recipient;
    string transactionDate;
    string type;
    double amount;
};
#endif
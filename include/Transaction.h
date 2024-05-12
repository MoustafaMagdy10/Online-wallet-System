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
    Transaction(const string &sender,const string &recipient,const double &amount,const string &type);
    Transaction(const string &sender,const string &recipient,const string &date,const string &type,const double &amount);
     static void addTransactionToStore(const Transaction &T);
    static string get_current_time();
    void setAmount(double amount);
    void setType(string type);
    string getType();
    string getSender();
    string getRecipient();
    double getAmount();
    string getTransactionDate();
    static stack<Transaction>getTransactions();
private:
    static stack<Transaction>transactionStore;
    string sender;
    string recipient;
    string transactionDate;
    string type;
    double amount;
};
#endif
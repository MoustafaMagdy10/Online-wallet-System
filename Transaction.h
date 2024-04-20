// 
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <chrono>

class Transaction {
public:
    Transaction();
    Transaction(const std::string& sender, const std::string& recipient, double amount, const std::string& type);
    static std::string get_current_time();

private:
    std::string sender;
    std::string recipient;
    std::string transactionDate;
    std::string type;
    double amount;
};

#endif

#include <string>
#include <chrono>
#include<iostream>
class Transaction {
public:
    Transaction();
    Transaction(string sender, string recipient, double amount, string type);
    static std::string get_current_time();
    void setSender(string sender);
    void setRecipient(string recipient);
    void setAmount(double amount);
    void setType(string type);
    void setTransactionnDate();
    string getType();
    string getSender();
    string getRecipient();
    double getAmount();
    string getTransactionnDate();
private:
    std::string sender;
    std::string recipient;
    std::string transactionDate;
    std::string type;
    double amount;
};
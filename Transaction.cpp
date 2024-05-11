
#include "Transaction.h"
#include <iomanip>

stack<Transaction> Transaction::transactionStore;

Transaction::Transaction()
{
}

Transaction::Transaction(const string &sender,const string &recipient,const double &amount,const string &type)
{
    this->sender = sender;
    this->recipient = recipient;
    this->amount = amount;
    this->type = type;
    this->transactionDate = Transaction::get_current_time();
}

void Transaction::addTransactionToStore(const Transaction &T){
    transactionStore.push(T);
}

void Transaction::Transaction::setAmount(double amount)
{
    this->amount = amount;
}
void Transaction::setType(string type)
{
    this->type = type;
}
string Transaction::getType()
{
    return this->type;
}
string Transaction::getSender()
{
    return this->sender;
}
string Transaction::getRecipient()
{
    return this->recipient;
}
double Transaction::getAmount()
{
    return this->amount;
}
string Transaction::getTransactionDate()
{
    return this->transactionDate;
}

stack<Transaction > Transaction::getTransactions()
{
    stack<Transaction> st = transactionStore;
    return st;
}

std::string Transaction::get_current_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *localTime = std::localtime(&currentTime);
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << localTime->tm_mday << "/"
       << std::setw(2) << std::setfill('0') << (localTime->tm_mon + 1) << "/"
       << std::setw(2) << std::setfill('0') << (localTime->tm_year + 1900);

    return ss.str();
}

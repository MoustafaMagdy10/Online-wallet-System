
#include "Transaction.h"

Transaction::Transaction(){
    
}

Transaction::Transaction(string sender, string recipient, double amount, string type) {
    this->sender = sender;
    this->recipient = recipient;
    this->amount = amount;
    this->type = type;
    this->transactionDate = Transaction::get_current_time();
}

void Transaction::setSender(string sender)
{
    this->sender = sender;
}
void Transaction::setRecipient(string recipient)
{
    this->recipient = recipient;
}
void Transaction::Transaction::setAmount(double amount)
{
    this->amount = amount;
}
void Transaction::setType(string type)
{
    this->type = type;
}
void Transaction::setTransactionnDate()
{
    this->transactionDate = Transaction::get_current_time();
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
string Transaction::getTransactionnDate()
{
    return this->transactionDate;
}

std::string Transaction::get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&current_time);
}


#include "Transaction.h"

Transaction::Transaction(){
    
}

Transaction::Transaction(const std::string& sender, const std::string& recipient, double amount, const std::string& type) {
    this->sender = sender;
    this->recipient = recipient;
    this->amount = amount;
    this->type = type;
    this->transactionDate = Transaction::get_current_time();
}

std::string Transaction::get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&current_time);
}

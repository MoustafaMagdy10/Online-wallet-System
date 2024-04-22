#include "User.h"

User::User(string userName,string password)
: Person(userName,password)
{
    admin = false;
}

void User::sendMoney(string recipientUsername, double amount)
{
}

void User::requestMoney(string senderUsername, double amount)
{
}

// double User::getBalance()
// {
//     return this->balance;
// }

User::~User()
{
    
}
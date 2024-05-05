#include "User.h"

User::User(const string &userName, const string &password)
    : Person(userName, password)
{
    admin = false;
    balance=0;
}

// void User::sendMoney()
// {

//     long double amount = 0;
// amountGetter:
//     cout << "Enter the amount you want to send:\n";
//     cin >> amount;
//     if (amount <= 0)
//     {
//         cout << "please enter a valid amount:\n";
//         goto amountGetter;
//     }
//     else if (currentUser->balance < amount)
//     {
//         cout << "No sufficient balance\n";
//     }

//     auto it = Person::getUserByName(recipientUsername);
//     if (it == nullptr or it->getAdminRole() == true)
//     {
//         cout << "No such a user exists\n";
//         return;
//     }

//     User *recipient = static_cast<User *>(it);

//     recipient->addMoney();
// }

// void User::requestMoney(string senderUsername, double amount)
// {
// }

long double User::getBalance()
{
    cout<<"al mohm al se7a\n";
    return this->balance;
}
void User::setBalance(double balance)
{
    this->balance = balance;
}

stack<Transaction> User::getTransactionHistory()
{
    return this->transactionHistory;
}
void User::addTransaction(Transaction transaction)
{
    this->transactionHistory.push(transaction);

}
void User::viewCurrrentBalance()
{
    double amount = this->getBalance();
    cout << "Your Current Balance is: " << amount << "\n";
}
void User::viewTansactionHistory()
{
    stack<Transaction> history = this->transactionHistory;
    cout << "Your Transaction History :\n";
    cout << "Sender            recipient           Date            Type            amount\n";
    while (!history.empty())
    {
        cout << (history.top()).getSender() << "            " << history.top().getRecipient() << "            " << history.top().getTransactionnDate() << "            " << history.top().getType() << "            " << history.top().getAmount() << "\n";
        history.pop();
    }


}
void User::viewTansForAdmin()
{
    stack<Transaction>history=this->transactionHistory;


    cout<<"Sender            recipient           Date            Type            amount\n";
    while(!history.empty())
    {
        cout<<(history.top()).getSender()<<"            "<<history.top().getRecipient()<<"            "<<history.top().getTransactionnDate()<<"            "<<history.top().getType()<<"            "<<history.top().getAmount()<<"\n";
        history.pop();
    }


}
 void User::editProfile()
 {
    this->editUserName();
    this->editPassword();
 }
 void User::addMoney()
 {
    double amount;
repeatAmount:
    cout << "Enter the amount of Money\n";
    cin >> amount;
    if (amount <= 0)
    {
        cout << "Invalid amount\n";
        goto repeatAmount;
    }
    this->balance = this->balance + amount;
    cout << "Money added successfully\n";
}
void User::logOut()
{
    cout << "You have successfully logged out\n";
    exit(0);
}

User::~User()
{
}
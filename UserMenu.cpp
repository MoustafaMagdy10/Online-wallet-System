#include "UserMenu.h"
#include "User.h"
#include "Person.h"
#include <iostream>


UserMenu::UserMenu(const int &choice)
{

ShowMenu:

    switch (choice)
    {
    case 6:
        // User::currentUser->viewCurrrentBalance();
        break;

    case 7:
        User::currentUser->viewTransactionHistory();
        break;

    case 8:
        sendMoney();
        break;
    }
    // else if (choice == "5")
    // {
    //     requestMoney();
    // }
    // else if (choice == "6")
    // {
    //     currentUser->addMoney();
    // }
    // else if (choice == "7")
    // {
    //     cout << "You have successfully logged out\n";
    //     exit(0);
    // }
}
void UserMenu::sendMoney()
{
    string type = "sent";
    string recipient;
    long double amount;

repeatUsername:
    cout << "Enter Recipient username\n";
    getline(cin, recipient);
    // to Find a recipient with the given username
    auto recipientObj = Person::getUserByName(recipient);

    if (recipientObj == nullptr or recipientObj->getAdminRole())
    {
        cout << "Invalid recipient\n";
        string choice;
        cout << "1 to enter another user name , any other key to back\n";
        getline(cin, choice);
        if (choice != "1")
        {
            return;
        }
        goto repeatUsername;
    }

    User *recipientObjOfUser = static_cast<User *>(recipientObj);
repeatAmount:
    cout << "Enter the amount of Money\n";
    string temp;

    getline(cin, temp);

    if (!Person::isNumber(temp))
    {
        cout << "Please, Enter a valid number:\n";
        goto repeatAmount;
    }

    amount = stold(temp);

    if (amount <= 0 || amount > User::currentUser->getBalance())
    {
        cout << "Invalid amount , you don't have a sufficient amount:\n";
        string choice;
        cout << "1 to enter another valid amount, any other key to back\n";
        cout << "your balance = " << User::currentUser->getBalance() << endl;
        getline(cin, choice);

        if (choice != "1")
        {
            return;
        }
        goto repeatAmount;
    }

    User::currentUser->setBalance((User::currentUser->getBalance()) - amount);
    recipientObjOfUser->setBalance(recipientObjOfUser->getBalance() + amount);

    string sender = User::currentUser->getUserName();
    Transaction trans(sender, recipient, amount, type);
    User::currentUser->addTransaction(trans);
    recipientObjOfUser->addTransaction(trans);
}

// void UserMenu::requestMoney(User *currentUser, map<string, Person *> personStore)
// {
//     string type = "requested";
//     string sender;
//     double amount;
// repeatUsername:
//     cout << "Enter sender username\n";
//     cin >> sender;

//     // to Find a recipient with the given username
//     auto senderObj = Person::getUserByName(sender);
//     if (senderObj == nullptr)
//     {
//         cout << "Invalid recipient\n";
//         goto repeatUsername;
//     }
//     // to downcast the recipient
//     User *senderObjOfUser = static_cast<User *>(senderObj);
// repeatAmount:
//     cout << "Enter the amount of Money\n";
//     cin >> amount;
//     if (amount <= 0 || amount > (senderObjOfUser->getBalance()))
//     {
//         cout << "Invalid amount\n";
//         goto repeatAmount;
//     }
//     senderObjOfUser->setBalance((senderObjOfUser->getBalance()) - amount);
//     currentUser->setBalance((currentUser->getBalance()) + amount);
//     string recipient = currentUser->getUserName();
//     Transaction trans(sender, recipient, amount, type);
//     currentUser->addTransaction(trans);
// }
UserMenu::~UserMenu()
{
}
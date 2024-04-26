#include "UserMenu.h"
#include "User.h"
#include "Person.h"
#include<iostream>
// // #include<string>
// // #include"Menu.h"
// // #include"Transaction.h"
// // #include"person.cpp"
// // using namespace std;
// // UserMenu::UserMenu(){}
UserMenu::UserMenu(User *currentUser,map<string, Person*> personStore)
{
    string choice;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    ShowMenu:
    cout<<"1.View Current Balance\n2.View history of transactions\n3.edit Profile\n4.Send money\n5.Request money\n6.Add Money\n7.Log out\n";
    cin>>choice;
    if(choice!="1" and choice!="2" and choice!="3" and choice!="4" and choice!="5" and choice!="6" and choice!="7")
    {
        cout<<"Invalid choice,enter a valid number\n";
        goto ShowMenu;
    }

    if(choice=="1")
    {
        currentUser->viewCurrrentBalance();
    }

    else if(choice=="2")
    {
        currentUser->viewTansactionHistory();
    }
    else if(choice=="3")
    {
        currentUser->editProfile();
    }

    else if(choice=="4")
    {
        sendMoney(currentUser,personStore);
    }
}
//     else if(choice=="5")
//     {
//         requestMoney(currentUser,personStore);
//     }
//     else if(choice=="6")
//     {
//        currentUser->addMoney();
//     }
//     else if(choice=="7")
//     {
//         cout<<"You have successfully logged out\n";
//         exit(0);
//     }
// } 
void UserMenu::sendMoney(User *currentUser,map<string, Person*> personStore)
{
    string type="sent";
    string recipient;
    double amount;
    repeatUsername:
    cout<<"Enter Recipient username\n";
    cin>>recipient;
     //to Find a recipient with the given username
    auto recipientObj=Person::getUserByName(recipient);
    if(recipientObj==nullptr)
    {
        cout<<"Invalid recipient\n";
        goto repeatUsername;
    }
    // //to downcast the recipient
    //User* recipientObjOfUser;
    // // if (recipientObj->knowAdminRule() == false)
    // // {
    User* recipientObjOfUser= static_cast<User *>(recipientObj);

//     //recipientObjOfUser
//    // }
    repeatAmount:
    cout<<"Enter the amount of Money\n";
    cin>>amount;
    if(amount<=0 || amount>currentUser->getBalance())
    {
        cout<<"Invalid amount\n";
        goto repeatAmount;
    }

    currentUser->setBalance((currentUser->getBalance())-amount);
    recipientObjOfUser->setBalance(recipientObjOfUser->getBalance());

    string sender=currentUser->getUserName();
    Transaction trans(sender,recipient,amount,type);  //error hna
    // currentUser->addTransaction(trans);
}
//     //currentUser->getTransactionHistory().push(trans);
//}
// //     Person *Person::getUserByName(const string &userName)
// // {
// //     map<string, Person *>::iterator temp;
// //     temp = personStore.find(userName);
// //     if (temp == personStore.end())
// //         return nullptr;
// //     return temp->second;
// // }

// void UserMenu::requestMoney(User *currentUser,map<string, Person*> personStore)
// {
//     string type="requested";
//     string sender;
//     double amount;
//     repeatUsername:
//     cout<<"Enter sender username\n";
//     cin>>sender;
//     //to Find a recipient with the given username
//     auto senderObj=Person::getUserByName(sender);
//     if(senderObj==nullptr)
//     {
//         cout<<"Invalid recipient\n";
//         goto repeatUsername;
//     }
//     //to downcast the recipient
//     if (senderObj->knowAdminRule() == false)
//     {
//         User* senderObj = static_cast<User*>(senderObj);
//     }
//     repeatAmount:
//     cout<<"Enter the amount of Money\n";
//     // cin>>amount;
//     // if(amount<=0 || amount>(senderObj->getBalance()))
//     // {
//     //     cout<<"Invalid amount\n";
//     //     goto repeatAmount;
//     // }
//     // ssenderObj->setBalance((senderObj->getBalance())-amount);
//     // currentUser->setBalance((currentUser->getBalance())+amount);
//     // string recipient=currentUser->getUserName();
//     // Transaction trans(sender,recipient,amount,type);
//     // currentUser->addTransaction(trans);
// }
// // // void UserMenu::addMoney(Person *currentPerson)
// // // {
// // //     double amount;
// // //     repeatAmount:
// // //     cout<<"Enter the amount of Money\n";
// // //     cin>>amount;
// // //     if(amount<=0)
// // //     {
// // //         cout<<"Invalid amount\n";
// // //         goto repeatAmount;
// // //     }
// // //     currentPerson->setBalance((currentPerson->getBalance())+amount);
// // //     cout<<"Money added successfully\n";
// // // }
// // // ''
// // // void UserMenu::logOut()
// // // {
// // //     cout<<"You have successfully logged out\n";
// // //     exit(0);
// // // }
// // ''
// UserMenu::~UserMenu()
// {

// }
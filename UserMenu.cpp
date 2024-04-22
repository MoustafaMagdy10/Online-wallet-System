#include "UserMenu.h"

// #include<iostream>
// #include<string>
// #include"Menu.h"
// #include"Transaction.h"
//#include"person.cpp"
// using namespace std;
// UserMenu::UserMenu(){}
// // UserMenu::UserMenu(Person *currentPerson,map<string, Person*> personStore)
// {
//     string choice;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

//     cout<<"1.View Current Balance\n2.View history of transactions\n3.edit Profile\n4.Send money\n5.Request money\n6.Add Money\n7.Log out\n";
//     cin>>choice;
//     if(choice!="1" and choice!="2" and choice!="3" and choice!="4" and choice!="5" and choice!="6" and choice!="7")
//     {
//         cout<<"Invalid choice,enter a valid number\n";
//         UserMenu(currentPerson,personStore);
//         return;
//     }

//     if(choice=="1")
//     {
//         UserMenu::viewCurrrentBalance(currentPerson);
//     }
//     else if(choice=="2")
//     {
//         UserMenu::tansactionHistory(currentPerson);
//     }
//     else if(choice=="3")
//     {
//         UserMenu::editProfile(currentPerson);
//     }
//     else if(choice=="4")
//     {

//     }
//     else if(choice=="5")
//     {
        
//     }
//     else if(choice=="6")
//     {
       
//     }
//     else if(choice=="7")
//     {
//         cout<<"You have successfully logged out\n";
//         exit(0);
//     }
// }
    
// // void UserMenu::viewCurrrentBalance(Person *currentPerson)
// // {
// //     double amount=currentPerson->getBalance();
// //     cout<<"Your Current Balance is: "<<amount<<"\n";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
// // }
// // void UserMenu::tansactionHistory(Person *currentPerson)
// // {
// //     stack<Transaction>history=currentPerson->geytTransactionHistory();
// //     cout<<"Transaction History::\n";
// //     cout<<"Sender      Recipient          Date            type               amount\n";
// //     while(!history.empty())
// //     {
// //         cout<<history.top().getSender()<<"      "<<history.top().getRecipient()<<"          "<<history.top().getType()<<"               "<<history.top().getAmount()<<"\n";
// //         history.pop();
// //     }
// // // }
// void UserMenu::editProfile(Person *currentPerson)
// {
//     currentPerson->editUserName();
//     currentPerson->editPassword();
// }

// void UserMenu::sendMoney(Person *currentPerson,map<string, Person*> personStore)
// {
//     string type="sent";
//     string recipient;
//     double amount;
//     repeatUsername:
//     cout<<"Enter Recipient username\n";
//     cin>>recipient;
//     auto recipientobj=personStore.find(recipient);
//     if(recipientobj==personStore.end())
//     {
//         cout<<"Invalid recipient\n";
//        goto repeatUsername;
//     }
//     repeatAmount:
//     cout<<"Enter the amount of Money\n";
//     cin>>amount;
// //     if(amount<=0 || amount>currentPerson->getBalance())
// //     {
// //         cout<<"Invalid amount\n";
// //         goto repeatAmount;
// //     }
// //     currentPerson->setBalance((currentPerson->getBalance())-amount);
// //     recipientobj->second->setBalance((recipientobj->second->getBalance())+amount);
// //     string sender=currentPerson->getUserName();
// //     Transaction trans(sender,recipient,amount,type);
// //     currentPerson->addTransaction(trans);
// // }
// }
// void UserMenu::requestMoney(Person *currentPerson,map<string, Person*> personStore)
// {
//     string type="requested";
//     string sender;
//     double amount;
//     repeatUsername:
//     cout<<"Enter sender username\n";
//     cin>>sender;
//     auto senderobj=personStore.find(sender);
//     if(personStore.find(sender)==personStore.end())
//     {
//         cout<<"Invalid recipient\n";
//         goto repeatUsername;
//     }
//     repeatAmount:
//     cout<<"Enter the amount of Money\n";
//     cin>>amount;
//     if(amount<=0 || amount>(senderobj->second->getBalance()))
//     {
//         cout<<"Invalid amount\n";
//         goto repeatAmount;
//     }
//     senderobj->second->setBalance((senderobj->second->getBalance())-amount);
//     currentPerson->setBalance((currentPerson->getBalance())+amount);
//     string recipient=currentPerson->getUserName();
//     Transaction trans(sender,recipient,amount,type);
//     currentPerson->addTransaction(trans);
// }
// void UserMenu::addMoney(Person *currentPerson)
// {
//     double amount;
//     repeatAmount:
//     cout<<"Enter the amount of Money\n";
//     cin>>amount;
//     if(amount<=0)
//     {
//         cout<<"Invalid amount\n";
//         goto repeatAmount;
//     }
//     currentPerson->setBalance((currentPerson->getBalance())+amount);
//     cout<<"Money added successfully\n";
// }
// void UserMenu::logOut()
// {
//     cout<<"You have successfully logged out\n";
//     exit(0);
// }
// UserMenu::~UserMenu()
// {

// }
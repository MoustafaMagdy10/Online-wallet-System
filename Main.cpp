#include<iostream>
#include "Person.cpp"
#include "Logs.cpp"
#include "Menu.cpp"
#include "Admin.cpp"
#include "User.cpp"
#include "Transaction.cpp"
 #include "UserMenu.cpp"
using namespace std;
int main(){
    //   Menu();
    //     return 0;
     Person *manger=new Person("manger","MmMnkfffd65");
    manger->addPerson("mousa","Mmkdfmdkf45",1);
    manger->addPerson("user1","Mmkdfmdkf45",0);
    manger->addPerson("user2","Mmkdfmdkf45",0);
    manger->addPerson("user3","Mmkdfmdkf45",0);
    Admin *ad1=static_cast<Admin*>(manger);
   // ad1->ViewAllUsers();
     User *user=static_cast<User*>(manger);
     // Transaction t1("user1","user2",150,"send");
     // user->addTransaction(t1);

   // ad1->ViewUser("user1");
 ad1->menueAdmin();
 // ad1->ViewUser("user1");
    // Person P("fjlkajf","fklashf");
    // Transaction::Transaction(string sender, string recipient, double amount, string type
    // Transaction t("menna","moustafa",50,"sent");
}
#include "Admin.h"

Admin::Admin()
: Person()
{
    
}
Admin::Admin(const string &userName,const string &password)
: Person(userName,password)
{
    admin = true;
}
void Admin:: ViewAllUsers() {


    //User::currentUser = static_cast<User *>(Person::currentPerson);
for (auto &person: Person::personStore) {
if (!person.second->admin) {
    User *user=static_cast<User *>(person.second);
    cout <<"Name:"<<user->userName<<endl<<"balance:"<<user->getBalance()<<endl;


   // cout<<"history:\n";
   // user->viewTansactionHistory();

}
}
    cout << "for more details Enter user name :\n";
    string name ;
    cin>>name;
    ViewUser(name);
}
void Admin::ViewUser(string name) {
    if (!personStore[name]->admin) {
        User *user=static_cast<User*>(personStore[name]);
        cout <<"Name:"<<user->userName<<endl<<"balance:"<<user->getBalance()<<endl;
        user->viewTansactionHistory();
    }
    else cout<<"invalid Name ";
}

Admin::~Admin()
{

}
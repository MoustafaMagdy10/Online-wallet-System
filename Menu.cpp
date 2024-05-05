#include "Menu.h"
#include "Person.h"
#include "User.h"
#include "Logs.h"
#include "Admin.h"
#include "UserMenu.h"

map<string, Person *> Person::personStore;
Person *Person::currentPerson = nullptr;
User *User::currentUser = nullptr;
Admin *Admin::currentAdmin = nullptr;
Menu::Menu()
{
    if (Person::currentPerson == nullptr)
    {
        Logs();
        Menu();
        return;
    }
    string choice;
    cout << "1 to edit username:\n2 to edit password:\n3 to logout:\n4 to show your admin role:\n5 to exit:\n";
    if(User::currentUser!=nullptr){
        cout<<"6 to show your balance:\n7 to view Tansaction History:\n8 to send money:\n ";
    }
    cin >> choice;

    if (st.find(choice) == st.end())
    {
        cout << "Enter a valid choice:\n";
        Menu();
        return;
    }

    int operation = stoi(choice);
    switch (operation)
    {
    case 1:
        Person::currentPerson->editUserName();
        break;
    case 2:
        Person::currentPerson->editPassword();
        break;
    case 3:
        Logs::logOut();
        break;
    case 4:
        Person::currentPerson->showMyRole();
        break;
    case 5:
        return;
    }
   
    if (User::currentUser != nullptr)
    {
       UserMenu U = UserMenu(operation);
    }
    Menu();
}

Menu::~Menu()
{
}
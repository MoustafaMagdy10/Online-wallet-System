#include "Menu.h"
#include "Person.h"
#include "User.h"
#include "Logs.h"
#include "Admin.h"

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
    cin >> choice;

    if (choice != "1" and choice != "2" and choice != "3" and choice != "4" and choice != "5"  )
    {
        Menu();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
        return;
    }
    if (choice == "1")
    {
        Person::currentPerson->editUserName();
    }
    if (choice == "2")
    {
        Person::currentPerson->editPassword();
    }
    if (choice == "3")
    {
        Logs::logOut();
    }
    if (choice == "4")
    {
        Person::currentPerson->showMyRole();
    }
    if (choice == "5")
    {
        return;
    }
    Menu();
}

Menu::~Menu()
{
}
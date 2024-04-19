#include "Menu.h"
#include "Person.h"
#include "Logs.h"

map<string, Person *> Person::personStore;
Person* Person::currentUser = nullptr;

Menu::Menu()
{
    if (Person::currentUser == nullptr)
    {
        Logs();
        Menu();
        return;
    }
    string choice;
    cout << "1 to edit username:\n2 to edit password:\n3 to logout\n4 to exit\n";
    cin >> choice;

    if (choice != "1" and choice != "2" and choice!="3" and choice!="4")
    {
        Menu();
        return;
    }
    if(choice == "1"){
        Person::currentUser->editUserName();
    }
    if(choice == "2"){
        Person::currentUser->editPassword();
    }
    if(choice == "3"){
        Logs::logOut();
    }
    if(choice == "4"){
        return;
    }
    Menu();
}

Menu::~Menu()
{
}
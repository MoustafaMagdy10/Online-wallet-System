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
    }
    // 1 edit username , 2 edit password ,
    int choice;
    cout << "1 to edit username:\n2 to edit password:\n3 to logout\n";
    cin >> choice;
    if (choice != 1 and choice != 2 and choice!=3)
    {
        Menu();
        return;
    }
    if(choice == 1){
        Person::currentUser->editUserName();
    }
    if(choice == 2){
        Person::currentUser->editPassword();
    }
    if(choice == 3){
        Logs::logOut();
    }
    Menu();
}

Menu::~Menu()
{
}
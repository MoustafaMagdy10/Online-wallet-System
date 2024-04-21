#include "Menu.h"
#include "Person.h"
#include "Logs.h"

map<string, Person *> Person::personStore;
Person *Person::currentUser = nullptr;
Menu::Menu()
{
    if (Person::currentUser == nullptr)
    {
        Logs();
        Menu();
        return;
    }
    string choice;
    cout << "1 to edit username:\n2 to edit password:\n3 to logout:\n4 to show your admin role:\n5 to exit:\n";
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
        Person::currentUser->editUserName();
        break;
    case 2:
        Person::currentUser->editPassword();
        break;
    case 3:
        Logs::logOut();
        break;
    case 4:
        Person::currentUser->showMyRole();
        break;
    case 5:
        return;
    }
    Menu();
}

Menu::~Menu()
{
}
#include "Logs.h"
#include "Person.h"

Logs::Logs()
{
    string login; // to login if 1 , register if 2
    cout << "to login choose 1 , to register choose 2 \n";
    cin >> login;
    if (login != "1" and login != "2")
    {
        cout << "please choose a valid number\n";
        Logs();
        return;
    }
    if (login == "1")
    {
        logIn();
    }
    else
    {
        register_();
    }
}

void Logs::register_()
{

    string userName, password;
    string choice;


    cout << "Enter username:\n";
    cin.ignore();
    getline(cin, userName);

name:
    if (Person::getUserByName(userName) != nullptr)
    {
        cout << "name is already taken\n";
    choiceName:
        cout << "select 1 to enter username again , 2 to back:\n";
        cin >> choice;
        if (choice != "1" and choice != "2")
        {
            cout << "Enter a valid number:\n";
            goto choiceName;
        }
        if (choice == "2")
            return;
        cout << "Enter username:\n";
        cin.ignore(); // Ignore the newline character left in the input stream
        getline(cin, userName);
        goto name;
    }

    cout << "password must be more then 8 characters containing uppercase letter and a number:\n";
    cout << "Enter password:\n";
    getline(cin, password);
pass:
    if (!Person::checkValidPassword(password))
    {
    choicePass:
        string choice;
        cout << "select 1 to enter password again  , 2 to back:\n";
        cin >> choice;
        if (choice != "1" and choice != "2")
        {
            cout << "Enter a valid number:\n";
            goto choicePass;
        }
        if (choice == "2")
            return;
        cout << "Enter your password:\n";
        cin.ignore();
        getline(cin, password);
        goto pass;
    }

    Person::addPerson(userName, password, false);
    Person::currentPerson = Person::getUserByName(userName);
    cout << "bono bono" << endl;
}

void Logs::logIn()
{

    string userName, password;
    cout << "enter your username :\n";
    cin.ignore();
    getline(cin, userName);

name:
    auto it = Person::getUserByName(userName);

    if (it == nullptr)
    {
        cout << "No such user:\n";
    choiceName:
        string choice;
        cout << "1 to enter username again , 2 to go back:\n";
        cin >> choice;
        if (choice != "1" and choice != "2")
        {
            cout << "Enter a valid number:\n";
            goto choiceName;
        }
        if (choice == "2")
            return;
        cout << "Enter your username:\n";
        cin.ignore();
        getline(cin, userName);
        goto name;
    }

    cout << "password must be more then 8 characters containing uppercase letter and a number:\n";
    cout << "Enter password:\n";
    getline(cin, password);

pass:
    if (!it->checkPassword(password, it))
    {
        cout << "passwords does not match:\n";
    choicePass:
        string choice;
        cout << "1 to enter password again  , 2 to go back:\n";
        cin >> choice;
        if (choice != "1" and choice != "2")
        {
            cout << "Enter a valid number:\n";
            goto choicePass;
        }
        if (choice == "2")
            return;
        cout << "Enter your password:\n";
        cin.ignore();
        getline(cin, password);
        goto pass;
    }

    Person::currentPerson = Person::getUserByName(userName);
    cout << "bono bono\n";
}

void Logs::logOut()
{
    Person::currentPerson = nullptr;
    User::currentUser = nullptr;
    Admin::currentAdmin = nullptr;
}

#include "Logs.h"
#include "Person.h"

Logs::Logs()
{
    int login; // to login if 1 , register if 2
    cout << "to login choose 1 , to register choose 2 \n";
    cin >> login;
    if (login != 1 and login != 2)
    {
        cout << "please choose a valid number\n";
        Logs();
        return;
    }
    string userName, password;
    cout << "7ot username wa pass\n";
    cin >> userName >> password;
    if (login == 1)
    {
        if (logIn(userName, password))
        {
            Person::currentUser = Person::getUserByName(userName);
        }
        else
        {
            cout << "either username or password is wrong please try again\n";
            Logs();
            return;
        }
    }
    else
    {
        if (register_(userName, password))
        {
            Person::currentUser = Person::getUserByName(userName);
        }
        else
        {
            cout << "Name is already exists\n";
            Logs();
            return;
        }
    }
    cout << "bono bono" << endl;
    // Logs();
}

bool Logs::register_(string userName, string password)
{

    if (Person::getUserByName(userName) == nullptr)
    {
        Person::addPerson(userName, password);
        return true;
    }

    return false;
}

bool Logs::logIn(string userName, string password)
{
    auto it = Person::getUserByName(userName);

    if (it == nullptr)
        return false;

    if (it->checkPassword(password,it))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Logs::logOut()
{
    Person::currentUser = nullptr;
}

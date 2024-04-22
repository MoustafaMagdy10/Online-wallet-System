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
    bool admin = false;
roleChoice:
    cout << "1 to register as a normal user , 2 to register as an admin , 3 to go back:\n";
    cin.ignore();
    getline(cin, choice);
    if (choice != "1" and choice != "2" and choice != "3")
    {
        cout << "Enter a valid choice:\n";
        goto roleChoice;
    }
    if (choice == "2")
    {
        cout << "Enter admin secret code:\n";
        string secretCode;
        getline(cin,secretCode);
    passCode:
        if (secretCode != "magdy al gamed")
        {
wrongPassCode:
            cout << "You have entered wrong secret code:\n";
            cout << "1 to enter secret code again , 2 to go back:\n";
            string choice;
            cin >> choice;
            if(choice != "1" and choice != "2")
            {
                cout << "Enter a valid choice:\n";
                cin >> choice;
                goto wrongPassCode;
            }
            if (choice == "1"){
                cout << "Enter admin secret code:\n";
                cin.ignore();
                getline(cin,secretCode);
                goto passCode;
            }
            else
                goto roleChoice;
        }
        cout<<"Secret code has been passed successfully:\n";
        admin = true;
    }

    if (choice == "3")
        return;
 
    cout << "Enter username:\n";
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

    Person::addPerson(userName, password, admin);
    Person::currentUser = Person::getUserByName(userName);
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

    Person::currentUser = Person::getUserByName(userName);
    cout << "bono bono\n";
}

void Logs::logOut()
{
    Person::currentUser = nullptr;
}

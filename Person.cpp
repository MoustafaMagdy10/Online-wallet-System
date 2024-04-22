#include <iostream>
#include "Person.h"

#include <cstdint>

#include "Admin.cpp"
#include "User.cpp"

Person::Person() {}
Person::Person(const string &userName, const string &password)
{
    this->userName = userName;
    this->password = hashPassword(password);
}
void Person::addPerson(const string &userName,const string &password,const bool &role)
{
    if (role)
        Person::personStore[userName] = new Admin(userName, password);
    else
        Person::personStore[userName] = new User(userName, password);
}

Person *Person::getUserByName(const string &userName)
{
    map<string, Person *>::iterator temp;
    temp = personStore.find(userName);
    if (temp == personStore.end())
        return nullptr;
    return temp->second;
}
void Person::editUserName()
{
    string userName;
    cout << "enter the name you want to change\n";
    cin >> userName;
    auto it = getUserByName(userName);
    if (it != nullptr)
    {
        cout << "Name already exits\n";
        editUserName();
        return;
    }
    personStore.erase(this->userName);
    personStore[userName] = currentPerson;
    currentPerson->userName = userName;
    cout << "name has been changed successfully\n";
}
void Person::showMyRole()
{
    if (admin)
        cout << "You are an admin:\n";
    else
        cout << "You are a user:\n";
}
bool Person::checkPassword(const string &password,const Person *p)
{
    uint64_t hash = hashPassword(password);
    return p->password == hash;
}
uint64_t Person::hashPassword(const string &password)
{
    uint64_t hash = 14695981039346656037ULL;
    for (auto c : password)
    {
        hash ^= static_cast<uint64_t>(c); // xor
        hash *= 1099511628211ULL;
    }
    return hash;
}
bool Person::checkValidPassword(const string &password)
{
    if (password.size() < 8)
    {
        cout << "Password is too short, Password must be more then 8 characters\n";
        return false;
    }
    bool number = false, upperCase = false;
    for (auto i : password)
    {
        if (isupper(i))
            upperCase = true;
        if (i <= '9' and i >= '0')
            number = true;
        if (number and upperCase)
            break;
    }
    if (!number or !upperCase)
    {

        cout << "Password is too weak, Password must contain a number and an uppercase letter\n";
        return false;
    }

    return true;
}
void Person::editPassword()
{
    string password;
    cout << "enter your current password\n";
    cin >> password;
    if (!checkPassword(password, Person::currentPerson))
    {
        cout << "you have entered wrong password\n";
        editPassword();
        return;
    }
passed:
    cout << "enter the new password\n";
    cin >> password;
    if (!checkValidPassword(password))
        goto passed;
    string temp;
    cout << "enter new password again\n";
    cin >> temp;
    if (temp != password)
    {
        goto passed;
    }
    currentPerson->password = hashPassword(password);
}
void Person::initializeUser()
{
    if (Person::currentPerson == nullptr)
        return;

    if (Person::currentPerson->admin == false)
    {

        User::currentPerson = static_cast<User *>(Person::currentPerson);
        Admin::currentAdmin = nullptr;
    }
    else
    {
        Admin::currentAdmin = static_cast<Admin *>(Person::currentPerson);
        User::currentPerson = nullptr;
    }
}
Person::~Person()
{
    for (auto i : personStore)
    {
        delete i.second;
    }
    Person::personStore.clear();
    Person::currentPerson = nullptr;
}
#include "Person.h"
#include <iostream>

Person::Person(string userName, string password)
{
    this->userName = userName;
    this->password = password;
}
void Person::addPerson(string userName, string password)
{
    // Person p(userName, password);
    Person::personStore[userName] = new Person(userName,password);
}

bool Person::checkPassword(string password,Person* p)
{
    return p->password == password;
}
Person *Person::getUserByName(string userName)
{
    map<string, Person*>::iterator temp;
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
    personStore[userName] = currentUser;
    currentUser->userName = userName;
    cout<<"name has been changed successfully\n";
}
bool Person:: checkValidPassword(string password){
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
        if (i <= '9' or i >= '0')
            number = true;
        if (number and upperCase)
            break;
    }
    if (!number or !upperCase){

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
    if (!checkPassword(password,Person::currentUser))
    {  
        // cout<<"correct password is:"<<this->password;
        cout << "you have entered wrong password\n";
        editPassword();
        return;
    }
passed:
    cout << "enter the new password\n";
    cin >> password;
    if(!checkValidPassword(password)) goto passed;
    string temp;
    cout << "enter new password again\n";
    cin >> temp;
    if (temp != password)
    {
        goto passed;
    }
    this->password = password;
}